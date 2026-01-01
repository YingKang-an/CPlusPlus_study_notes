# 设置最小CMake版本要求
cmake_minimum_required(VERSION 3.10)  

# 项目名称
project(CameraTest)                   

# 指定C++标准为C++11
set(CMAKE_CXX_STANDARD 11)            

# 自动查找OpenCV和大恒SDK
find_package(OpenCV REQUIRED)
find_package(Daheng REQUIRED)

# 生成可执行文件
add_executable(main main.cpp)
add_executable(MyMain MyMain.cpp)
add_executable(1 1.cpp)

# 链接库+包含头文件
target_link_libraries(main ${OpenCV_LIBS} ${Daheng_LIBRARIES})
target_include_directories(main PUBLIC ${OpenCV_INCLUDE_DIRS} ${Daheng_INCLUDE_DIRS})

target_link_libraries(MyMain ${OpenCV_LIBS} ${Daheng_LIBRARIES})
target_include_directories(MyMain PUBLIC ${OpenCV_INCLUDE_DIRS} ${Daheng_INCLUDE_DIRS})

target_link_libraries(1 ${OpenCV_LIBS} ${Daheng_LIBRARIES})
target_include_directories(1 PUBLIC ${OpenCV_INCLUDE_DIRS} ${Daheng_INCLUDE_DIRS})