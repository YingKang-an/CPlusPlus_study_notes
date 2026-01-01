#include <iostream>
#include <cstring>
#include <cstdlib>
#include "GxIAPI.h"
#include "DxImageProc.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// 全局变量：相机句柄+核心参数（只保留曝光、增益、对比度）
GX_DEV_HANDLE hDev = NULL;
const int WIDTH = 640;
const int HEIGHT = 480;
int exposure = 1000;    // 曝光时间（us，初始1ms）
int gain = 0;           // 增益（dB，初始0）
int contrast = 50;      // 对比度（0-100，初始50）

// 滑动条回调函数（删除饱和度相关）
void onExposureChange(int val, void*)
{
    if (hDev != NULL)
    {
        double expVal = max(100.0, (double)val);
        GXSetFloat(hDev, GX_FLOAT_EXPOSURE_TIME, expVal);
        exposure = val;
    }
}

void onGainChange(int val, void*)
{
    if (hDev != NULL) 
    {
        double gainVal = max(0.0, (double)val);
        GXSetFloat(hDev, GX_FLOAT_GAIN, gainVal);
        gain = val;
    }
}

void onContrastChange(int val, void*)
{
    if (hDev != NULL) 
    {
        GXSetFloat(hDev, GX_FLOAT_CONTRAST, (double)val);
        contrast = val;
    }
}

// 安全退出函数（保留原逻辑）
void SafeExit(GX_STATUS status, const string& msg = "")
{
    if (!msg.empty())
    {
        cerr << (status == GX_STATUS_SUCCESS ? "[Info] " : "[Error] ") << msg << " (Code: " << status << ")" << endl;
    }
    if (hDev != NULL)
    {
        GXStreamOff(hDev);
        GXCloseDevice(hDev);
        hDev = NULL;
    }
    GXCloseLib();
    destroyAllWindows();
    exit(status == GX_STATUS_SUCCESS ? 0 : -1);
}

int main() 
{
    GX_STATUS status = GX_STATUS_SUCCESS;
    uint32_t devNum = 0;
    PGX_FRAME_BUFFER pFrameBuf = NULL;
    uint8_t* pRGB = new uint8_t[WIDTH * HEIGHT * 3];
    memset(pRGB, 0, WIDTH * HEIGHT * 3);

    // 1. 初始化SDK+打开相机
    status = GXInitLib();
    if (status != GX_STATUS_SUCCESS) SafeExit(status, "SDK初始化失败");

    status = GXUpdateDeviceList(&devNum, 1000);
    if (status != GX_STATUS_SUCCESS) SafeExit(status, "枚举设备失败");
    if (devNum == 0) SafeExit((GX_STATUS)-1, "未检测到相机设备");
    cout << "检测到 " << devNum << " 台相机" << endl;

    status = GXOpenDeviceByIndex(1, &hDev);
    if (status != GX_STATUS_SUCCESS) SafeExit(status, "打开相机失败");
    cout << "相机打开成功" << endl;

    // 2. 配置触发模式
    status = GXSetEnumValue(hDev, "TriggerMode", GX_TRIGGER_MODE_OFF);
    if (status != GX_STATUS_SUCCESS) SafeExit(status, "配置触发模式失败");

    // 3. 创建窗口+添加3个滑动条（删除饱和度）
    namedWindow("Camera Live (Adjust Params)", WINDOW_AUTOSIZE);
    createTrackbar("Exposure(us)", "Camera Live (Adjust Params)", &exposure, 10000, onExposureChange);
    createTrackbar("Gain(dB)", "Camera Live (Adjust Params)", &gain, 20, onGainChange);
    createTrackbar("Contrast(0-100)", "Camera Live (Adjust Params)", &contrast, 100, onContrastChange);
    // 初始化参数
    onExposureChange(exposure, NULL);
    onGainChange(gain, NULL);
    onContrastChange(contrast, NULL);

    // 4. 采集+实时显示
    status = GXStreamOn(hDev);
    if (status != GX_STATUS_SUCCESS) SafeExit(status, "开采失败");
    cout << "开始实时显示，按 ESC 键退出" << endl;

    while (true) 
    {
        status = GXDQBuf(hDev, &pFrameBuf, 1000);
        if (status == GX_STATUS_SUCCESS && pFrameBuf->nStatus == GX_FRAME_STATUS_SUCCESS) {
            VxInt32 dxStatus = DxRaw8toRGB24(pFrameBuf->pImgBuf, pRGB, WIDTH, HEIGHT, RAW2RGB_NEIGHBOUR, BAYERRG, false);
            if (dxStatus == DX_OK)
            {
                Mat img(HEIGHT, WIDTH, CV_8UC3, pRGB);
                imshow("Camera Live (Adjust Params)", img);
                if (waitKey(1) == 27) break;
            }
            else
            {
                cerr << "[Error] 格式转换失败 (Code: " << dxStatus << ")" << endl;
            }
            GXQBuf(hDev, pFrameBuf);
        } else {
            cerr << "[Error] 图像采集失败 (Code: " << status << ")" << endl;
            break;
        }
    }

    SafeExit(GX_STATUS_SUCCESS, "程序正常退出");
    delete[] pRGB;
    return 0;
}

