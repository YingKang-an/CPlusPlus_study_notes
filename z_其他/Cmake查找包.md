# CMake 查找包机制笔记
# find_package
###### 2026.01.01

## 核心概念
CMake 执行 `find_package(XXX REQUIRED)` 时，**不是随意乱找**，而是遵循一套**严格的搜索顺序**  
只有把包放在“标准位置”，CMake 才能自动找到；否则必须手动指定路径

## CMake 自动搜索路径顺序（从高到低）

1. **用户手动指定**（优先级最高）
   - CMakeLists.txt 中：
     ```cmake
     set(XXX_DIR /某个路径)
     list(APPEND CMAKE_PREFIX_PATH "/某个路径")
     ```
   - 命令行：
     ```bash
     cmake .. -DXXX_DIR=/路径 -DCMAKE_PREFIX_PATH=/路径
     ```

2. **CMAKE_PREFIX_PATH 变量**
   - 你可以手动添加常用路径（如 /usr/local）

3. **系统标准前缀路径**（CMake 默认搜索这些目录）
   - /usr
   - /usr/local
   - /opt
   - /sw（macOS 常见）
   - /etc

   在每个前缀下搜索以下子目录：
   - <prefix>/lib/cmake/XXX/
   - <prefix>/lib/<arch>/cmake/XXX/
   - <prefix>/share/cmake/XXX/
   - <prefix>/cmake/

4. **环境变量**
   - `export XXX_DIR=/某个路径`
   - `export XXX_ROOT=/某个路径`

5. **CMAKE_MODULE_PATH**（手动添加的模块路径）
   - 用于查找老式的 FindXXX.cmake 脚本

6. **CMake 自带模块**
   - /usr/share/cmake/Modules/FindXXX.cmake 等

## 实际例子对比（OpenCV 与大恒相机）

| 包名                  | 典型 Config 文件位置                                      | 是否自动找到 | 说明 |
|-----------------------|-----------------------------------------------------------|--------------|------|
| OpenCV（apt 安装）    | /usr/lib/x86_64-linux-gnu/cmake/opencv4/OpenCVConfig.cmake | 是           | 在 /usr/ 下，完全符合标准路径 |
| 大恒 Daheng（.run 安装） | /usr/local/lib/cmake/Daheng/DahengConfig.cmake            | 是           | 在 /usr/local/ 下，CMake 默认搜索这里 |
| 大恒老版本（无 Config） | 只有头文件在 /usr/local/Galaxy_camera/inc                 | 否           | 没有 Config 文件，需要手动指定 |

## 实用调试命令

```bash
# 查看 CMake 详细搜索过程
cmake .. -DCMAKE_FIND_DEBUG_MODE=ON

# 查看 OpenCV 被找到的路径（示例）
pkg-config --cflags opencv4
pkg-config --libs opencv4

# 查看 CMake 缓存中的路径
cat build/CMakeCache.txt | grep OpenCV
```

## 小贴士：让 CMake “自己找到”包

1. **优先选择提供 XXXConfig.cmake 的安装方式**（新版大恒已经支持）
2. **源码或手动安装时指定标准前缀**：
   ```bash
   ./configure --prefix=/usr/local
   cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
   ```
3. **CMakeLists.txt 中手动帮忙**（最常用）：
   ```cmake
   # 推荐写在 find_package 前面
   list(APPEND CMAKE_PREFIX_PATH "/usr/local")
   list(APPEND CMAKE_PREFIX_PATH "/usr/local/Galaxy_camera")

   find_package(OpenCV REQUIRED)
   find_package(Daheng REQUIRED)   # 大恒相机
   ```
