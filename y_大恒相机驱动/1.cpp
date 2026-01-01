#include "GxIAPI.h"
#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>

using namespace std;

// 大恒相机操作类（完全适配Linux SDK）
class DaHengCamera
{
private:
    GX_STATUS     m_emStatus = GX_STATUS_SUCCESS;    // SDK操作状态
    uint32_t      m_ui32DeviceNum = 0;               // 可用设备数量
    GX_DEV_HANDLE m_hDevice = NULL;                  // 设备句柄
    GX_OPEN_PARAM m_stOpenParam{};                   // 设备打开参数

    // 私有函数：释放pszContent内存
    void FreeContentMemory()
    {
        if (m_stOpenParam.pszContent != nullptr)
        {
            delete[] m_stOpenParam.pszContent;
            m_stOpenParam.pszContent = nullptr;
        }
    }

public:
    // 构造函数：初始化SDK
    DaHengCamera()
    {
        // Linux下GXInitLib无需额外参数
        m_emStatus = GXInitLib();
        if (m_emStatus != GX_STATUS_SUCCESS)
        {
            cerr << "GXInitLib 初始化失败！状态码：" << m_emStatus << endl;
            throw runtime_error("SDK初始化失败，状态码：" + to_string(m_emStatus));
        }
        cout << "[INFO] SDK初始化成功" << endl;
        m_stOpenParam.pszContent = nullptr;
    }

    // 枚举所有可用设备
    bool EnumAllDevices() 
    {
        // Linux下GXUpdateAllDeviceList参数和Windows一致
        m_emStatus = GXUpdateAllDeviceList(&m_ui32DeviceNum, 1000);
        if (m_emStatus != GX_STATUS_SUCCESS) 
        {
            cerr << "[ERROR] 枚举设备失败！状态码：" << m_emStatus << endl;
            return false;
        }
        if (m_ui32DeviceNum == 0) 
        {
            cerr << "[ERROR] 无可用设备！" << endl;
            return false;
        }
        cout << "[INFO] 成功枚举到 " << m_ui32DeviceNum << " 台可用设备" << endl;
        return true;
    }

    // 打开设备（Linux适配版）
    bool OpenDevice(const string& content,
                    GX_OPEN_MODE openMode = GX_OPEN_INDEX,
                    GX_ACCESS_MODE accessMode = GX_ACCESS_EXCLUSIVE) 
    {
        FreeContentMemory();

        // 配置打开参数
        m_stOpenParam.accessMode = accessMode;
        m_stOpenParam.openMode = openMode;

        // Linux下用strncpy替换strcpy_s，手动加结束符
        size_t contentLen = content.length() + 1;
        m_stOpenParam.pszContent = new char[contentLen];  
        strncpy(m_stOpenParam.pszContent, content.c_str(), contentLen);
        m_stOpenParam.pszContent[contentLen - 1] = '\0'; // 强制添加字符串结束符

        // 打开设备
        m_emStatus = GXOpenDevice(&m_stOpenParam, &m_hDevice);
        if (m_emStatus != GX_STATUS_SUCCESS) 
        {
            cerr << "[ERROR] 打开设备失败！状态码：" << m_emStatus << endl;
            FreeContentMemory();
            return false;
        }
        cout << "[INFO] 成功打开设备，句柄：" << m_hDevice << endl;
        return true;
    }

    // 业务操作：适配Linux版GXGetIntValue接口
    void DoBusiness() 
    {
        if (m_hDevice == NULL) 
        {
            cerr << "[ERROR] 设备未打开，无法执行业务操作！" << endl;
            return;
        }
        cout << "[INFO] 设备已打开，开始读取整型参数信息" << endl;

        // ========== 示例1：读取曝光时间（ExposureTime） ==========
        GX_INT_VALUE stExposure; // Linux下用结构体存储参数信息
        // Linux版GXGetIntValue：参数2是字符串，参数3是GX_INT_VALUE结构体
        m_emStatus = GXGetIntValue(m_hDevice, "ExposureTime", &stExposure);
        if (m_emStatus == GX_STATUS_SUCCESS) 
        {
            cout << "[INFO] 曝光时间参数信息：" << endl;
            cout << "  当前值：" << stExposure.nValue << " μs" << endl;
            cout << "  最小值：" << stExposure.nMin << " μs" << endl;
            cout << "  最大值：" << stExposure.nMax << " μs" << endl;
            cout << "  步长：" << stExposure.nInc << " μs" << endl;
        } 
        else 
        {
            cerr << "[ERROR] 读取曝光时间失败！状态码：" << m_emStatus << endl;
        }

        // ========== 示例2：只读取增益的当前值（Gain） ==========
        GX_INT_VALUE stGain;
        m_emStatus = GXGetIntValue(m_hDevice, "Gain", &stGain);
        if (m_emStatus == GX_STATUS_SUCCESS) 
        {
            cout << "[INFO] 增益当前值：" << stGain.nValue << endl;
        }
        else
        {
            cerr << "[ERROR] 读取增益失败！状态码：" << m_emStatus << endl;
        }
    }

    // 关闭设备
    bool CloseDevice() 
    {
        FreeContentMemory();
        if (m_hDevice == NULL) 
        {
            cout << "[INFO] 无已打开的设备，无需关闭" << endl;
            return true;
        }
        m_emStatus = GXCloseDevice(m_hDevice);
        if (m_emStatus != GX_STATUS_SUCCESS) 
        {
            cerr << "[ERROR] 关闭设备失败！状态码：" << m_emStatus << endl;
            return false;
        }
        cout << "[INFO] 成功关闭设备" << endl;
        m_hDevice = NULL;
        return true;
    }

    // 析构函数：释放资源
    ~DaHengCamera() 
    {
        CloseDevice();
        // 释放SDK库资源
        m_emStatus = GXCloseLib();
        if (m_emStatus != GX_STATUS_SUCCESS) 
        {
            cerr << "[ERROR] 释放SDK库资源失败！状态码：" << m_emStatus << endl;
        } 
        else 
        {
            cout << "[INFO] SDK库资源已成功释放" << endl;
        }
    }
};

// 主函数
int main(int argc, char* argv[]) 
{
    try 
    {
        // 创建相机对象（自动初始化SDK）
        DaHengCamera camera;

        // 枚举可用设备
        if (!camera.EnumAllDevices()) 
        {
            return -1;
        }

        // 按索引打开第1台设备
        if (!camera.OpenDevice("1")) 
        {
            return -1;
        }

        // 读取参数
        camera.DoBusiness();

        // 关闭设备
        camera.CloseDevice();
    } 
    catch (const exception& e) 
    {
        cerr << "[FATAL] 程序异常：" << e.what() << endl;
        return -1;
    }

    cout << "[INFO] 程序正常结束" << endl;
    return 0;
}
