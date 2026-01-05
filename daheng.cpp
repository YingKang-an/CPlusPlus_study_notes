
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <memory>

// OpenCV 头文件
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

// 大恒相机 SDK 头文件
#include "GxIAPI.h"
#include "DxImageProc.h"

// 使用标准命名空间
using namespace std;
using namespace cv;

// --- 定义统一的回调数据结构和独立的回调函数 ---

struct TrackbarData {
    GX_DEV_HANDLE hDevice;
    string paramName;
    TrackbarData(GX_DEV_HANDLE handle, const string& name) : hDevice(handle), paramName(name) {}
};

void onExposureChanged(int value, void* userdata) {
    TrackbarData* data = static_cast<TrackbarData*>(userdata);
    if (data && data->hDevice) {
        GXSetFloatValue(data->hDevice, data->paramName.c_str(), static_cast<double>(value));
    }
}

void onGainChanged(int value, void* userdata) {
    TrackbarData* data = static_cast<TrackbarData*>(userdata);
    if (data && data->hDevice) {
        GXSetFloatValue(data->hDevice, data->paramName.c_str(), static_cast<double>(value));
    }
}

void onBalanceChanged(int value, void* userdata) {
    TrackbarData* data = static_cast<TrackbarData*>(userdata);
    if (data && data->hDevice) {
        GXSetEnumValueByString(data->hDevice, "BalanceRatioSelector", data->paramName.c_str());
        GXSetFloatValue(data->hDevice, "BalanceRatio", static_cast<double>(value) / 100.0);
    }
}

void onBlackLevelChanged(int value, void* userdata) {
    TrackbarData* data = static_cast<TrackbarData*>(userdata);
    if (data && data->hDevice) {
        GXSetFloatValue(data->hDevice, data->paramName.c_str(), static_cast<double>(value));
    }
}

void onWidthChanged(int value, void* userdata) {
    TrackbarData* data = static_cast<TrackbarData*>(userdata);
    if (!data || !data->hDevice) return;

    GX_INT_VALUE stMaxWidth;
    GXGetIntValue(data->hDevice, "WidthMax", &stMaxWidth);
    
    int newWidth = (value / 4) * 4;
    if (newWidth < 4) newWidth = 4;
    if (newWidth > stMaxWidth.nCurValue) newWidth = stMaxWidth.nCurValue;

    GXSetIntValue(data->hDevice, "OffsetX", (stMaxWidth.nCurValue - newWidth) / 2);
    GXSetIntValue(data->hDevice, "Width", newWidth);
}

void onHeightChanged(int value, void* userdata) {
    TrackbarData* data = static_cast<TrackbarData*>(userdata);
    if (!data || !data->hDevice) return;

    GX_INT_VALUE stMaxHeight;
    GXGetIntValue(data->hDevice, "HeightMax", &stMaxHeight);

    int newHeight = (value / 2) * 2;
    if (newHeight < 2) newHeight = 2;
    if (newHeight > stMaxHeight.nCurValue) newHeight = stMaxHeight.nCurValue;

    GXSetIntValue(data->hDevice, "OffsetY", (stMaxHeight.nCurValue - newHeight) / 2);
    GXSetIntValue(data->hDevice, "Height", newHeight);
}

void onFrameRateChanged(int value, void* userdata) {
    TrackbarData* data = static_cast<TrackbarData*>(userdata);
    if (data && data->hDevice) {
        GXSetFloatValue(data->hDevice, data->paramName.c_str(), static_cast<double>(value));
    }
}

// --- 主函数 ---
int main(int argc, char* argv[])
{
    GX_STATUS emStatus = GX_STATUS_SUCCESS;
    GX_DEV_HANDLE hDevice = NULL;
    uint32_t ui32DeviceNum = 0;

    emStatus = GXInitLib();
    if (emStatus != GX_STATUS_SUCCESS) {
        std::cerr << "GXInitLib failed." << std::endl;
        return -1;
    }

    emStatus = GXUpdateAllDeviceList(&ui32DeviceNum, 1000);
    if ((emStatus != GX_STATUS_SUCCESS) || (ui32DeviceNum <= 0)) {
        std::cerr << "GXUpdateAllDeviceList failed or no device found." << std::endl;
        GXCloseLib();
        return -1;
    }
    std::cout << "Found " << ui32DeviceNum << " device(s)." << std::endl;

    GX_OPEN_PARAM stOpenParam;
    stOpenParam.accessMode = GX_ACCESS_EXCLUSIVE;
    stOpenParam.openMode = GX_OPEN_INDEX;
    stOpenParam.pszContent = (char*)"1";
    
    emStatus = GXOpenDevice(&stOpenParam, &hDevice);
    if (emStatus != GX_STATUS_SUCCESS) {
        std::cerr << "设备打开失败" << std::endl;
        GXCloseLib();
        return -1;
    }
    std::cout << "设备打开成功" << std::endl;

    const string controlWindowName = "Camera Controls";
    cv::namedWindow(controlWindowName, cv::WINDOW_NORMAL);

    vector<shared_ptr<TrackbarData>> trackbarDataList;

    struct ParamInfo {
        string displayName;
        string sdkName;
        int maxValue;
        void (*callback)(int, void*);
    };
    
    vector<ParamInfo> params = {
        { "Exposure Time (us)",   "ExposureTime",      50000,  onExposureChanged   },
        { "Gain",                 "Gain",              100,    onGainChanged       },
        { "Red Balance (x0.01)",  "Red",               200,    onBalanceChanged    },
        { "Blue Balance (x0.01)", "Blue",              200,    onBalanceChanged    },
        { "Black Level",          "BlackLevel",        100,    onBlackLevelChanged },
        { "Width",                "Width",             1920,   onWidthChanged      },
        { "Height",               "Height",            1080,   onHeightChanged     },
        { "Frame Rate (FPS)",     "AcquisitionFrameRate", 60, onFrameRateChanged  },
    };

    for (const auto& param : params) {
        auto data = make_shared<TrackbarData>(hDevice, param.sdkName);
        trackbarDataList.push_back(data);

        int initialPos = 0;
        if (param.displayName.find("Balance") != string::npos) {
            GXSetEnumValueByString(hDevice, "BalanceRatioSelector", param.sdkName.c_str());
            GX_FLOAT_VALUE stValue;
            GXGetFloatValue(hDevice, "BalanceRatio", &stValue);
            initialPos = static_cast<int>(stValue.dCurValue * 100);
        } else if (param.displayName.find("Frame Rate") != string::npos) {
            GX_FLOAT_VALUE stValue;
            GXGetFloatValue(hDevice, param.sdkName.c_str(), &stValue);
            initialPos = static_cast<int>(stValue.dCurValue);
        } else if (param.displayName.find("Width") != string::npos || param.displayName.find("Height") != string::npos) {
            GX_INT_VALUE stValue;
            GXGetIntValue(hDevice, param.sdkName.c_str(), &stValue);
            initialPos = static_cast<int>(stValue.nCurValue);
        } else {
            GX_FLOAT_VALUE stValue;
            GXGetFloatValue(hDevice, param.sdkName.c_str(), &stValue);
            initialPos = static_cast<int>(stValue.dCurValue);
        }
        
        cv::createTrackbar(param.displayName, controlWindowName, NULL, param.maxValue, param.callback, data.get());
        cv::setTrackbarPos(param.displayName, controlWindowName, initialPos);
    }

    emStatus = GXSetEnumValueByString(hDevice, "PixelFormat", "BayerBG8");
    if (emStatus != GX_STATUS_SUCCESS) {
        std::cerr << "Failed to set PixelFormat to BayerBG8. Trying BayerRG8..." << std::endl;
        emStatus = GXSetEnumValueByString(hDevice, "PixelFormat", "BayerRG8");
        if (emStatus != GX_STATUS_SUCCESS) {
             std::cerr << "Failed to set PixelFormat to BayerRG8. Please check camera compatibility." << std::endl;
        }
    }

    GXSetEnumValueByString(hDevice, "ExposureMode", "Timed");
    GXSetEnumValueByString(hDevice, "TriggerMode", "Off");

#ifdef __linux__
    emStatus = GXStreamOn(hDevice);
#else
    emStatus = GXSetCommandValue(hDevice, GX_COMMAND_ACQUISITION_START);
#endif
    if (emStatus != GX_STATUS_SUCCESS) {
        std::cerr << "图像捕获失败" << std::endl;
        GXCloseDevice(hDevice);
        GXCloseLib();
        cv::destroyAllWindows();
        return -1;
    }
    std::cout << "开始捕获图像,按'q'退出" << std::endl;

    const string liveViewWindowName = "相机画面 (彩色)";
    cv::namedWindow(liveViewWindowName, cv::WINDOW_NORMAL);
    
    auto start_time = std::chrono::high_resolution_clock::now();
    int frame_count = 0;

    while (true) {
        GX_FRAME_BUFFER* pFrameBuffer = NULL;
        emStatus = GXDQBuf(hDevice, &pFrameBuffer, 100);
        if (emStatus == GX_STATUS_SUCCESS) {
            if (pFrameBuffer->nStatus == GX_FRAME_STATUS_SUCCESS) {
                
                cv::Mat colorImage(pFrameBuffer->nHeight, pFrameBuffer->nWidth, CV_8UC3);

                // **【核心修正】添加了 bFlip 参数**
                // 最后一个参数 false 表示不进行水平翻转。
                DxRaw8toRGB24(pFrameBuffer->pImgBuf, colorImage.data, pFrameBuffer->nWidth, pFrameBuffer->nHeight, RAW2RGB_NEIGHBOUR, BAYERBG, false);
                
                frame_count++;
                auto current_time = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = current_time - start_time;
                if (elapsed.count() >= 1.0) {
                    double fps = frame_count / elapsed.count();
                    string fps_text = "Actual FPS: " + to_string(static_cast<int>(fps));
                    putText(colorImage, fps_text, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
                    start_time = current_time;
                    frame_count = 0;
                }
                
                cv::imshow(liveViewWindowName, colorImage);
            }
            (void)GXQBuf(hDevice, pFrameBuffer);
        }

        if (cv::waitKey(1) == 'q') {
            std::cout << "退出图像捕获" << std::endl;
            break;
        }
    }

#ifdef __linux__
    emStatus = GXStreamOff(hDevice);
#else
    emStatus = GXSetCommandValue(hDevice, GX_COMMAND_ACQUISITION_STOP);
#endif

    if (hDevice != NULL) {
        GXCloseDevice(hDevice);
    }

    GXCloseLib();
    cv::destroyAllWindows();

    return 0;
}

