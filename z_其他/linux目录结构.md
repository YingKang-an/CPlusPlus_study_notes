# <center><font color=orange>Linux目录结构</font></center>
###### 2026.01.01
## **1.Linux路径的描述方式**
- 在linux中，路径层级关系用`/`表示<br>
[![pZNxmgx.md.png](https://s41.ax1x.com/2026/01/01/pZNxmgx.md.png)](https://imgchr.com/i/pZNxmgx)<br>
Linux只有一个顶级目录，叫`根目录`
Windows有多个，即`各个符盘`
- 注意
    - 开头的`/`代表`根目录`
    - 后面的`/`代表`层级关系`
## 2.根目录树
>tree -L 1/
```
.
├── bin -> usr/bin              # 基本命令（已合并到 /usr/bin）
├── bin.usr-is-merged           # 【Ubuntu特有】标记 /bin 已合并完成
├── boot                        # 启动文件（内核、GRUB）
├── cdrom                       # 光盘挂载点（遗留，基本空）
├── dev                         # 设备文件（硬件抽象）
├── etc                         # 全局配置文件
├── home                        # 用户家目录（你的私人空间）
├── lib -> usr/lib              # 库文件链接（合并）
├── lib64 -> usr/lib64          # 64位库链接
├── lib.usr-is-merged           # 【Ubuntu特有】标记 /lib 已合并
├── lost+found                  # 文件系统修复孤儿文件（正常空）
├── media                       # U盘等可移动设备自动挂载
├── mnt                         # 手动临时挂载点
├── opt                         # 第三方软件可选位置
├── proc                        # 进程/内核信息（虚拟）
├── root                        # root 用户家目录
├── run                         # 运行时临时数据（重启清空）
├── sbin -> usr/sbin            # 系统管理命令链接
├── sbin.usr-is-merged          # 【Ubuntu特有】标记 /sbin 已合并
├── snap                        # Snap 包软件目录
├── srv                         # 服务数据（网站等）
├── swap.img                    # 交换文件（虚拟内存，轻量版常用）
├── sys                         # 内核设备信息（虚拟）
├── tmp                         # 临时文件（重启清空）
├── usr                         # 用户程序和数据（最大目录）
└── var                         # 可变数据（日志、缓存）
```
## 3.Linux 软件/SDK 下载与安装位置笔记
###### 2026.01.02

## 软件安装位置分类

Linux 严格区分**系统管理安装**和**用户手动安装**，这就是为什么 OpenCV 去 /usr/lib，大恒相机去 /usr/local 的原因

| 安装方式                  | 示例命令或操作                                  | 临时下载位置                          | 最终安装位置（核心文件去哪里）                          | 特点与原因 |
|---------------------------|------------------------------------------------|---------------------------------------|---------------------------------------------------------|------------|
| **apt 包管理器安装**      | `sudo apt install libopencv-dev`               | /var/cache/apt/archives/（.deb 包）   | 分散到 /usr/ 下<br>• 可执行 → /usr/bin/<br>• 库 → /usr/lib/ 或 /usr/lib/x86_64-linux-gnu/<br>• 头文件 → /usr/include/<br>• 文档 → /usr/share/doc/ | 系统统一管理<br>位置固定、标准<br>适合系统级软件<br>卸载干净（apt remove） |
| **手动 .run / .sh 安装**  | 大恒相机 Galaxy_camera.run<br>某些驱动/SDK      | 你浏览器下载的 ~/下载 或桌面          | 通常整个文件夹放到 **/usr/local/**<br>• 完整目录 → /usr/local/Galaxy_camera/<br>• 库 → /usr/local/lib/<br>• 可执行 → /usr/local/bin/ | 用户本地安装<br>不干扰系统软件<br>方便卸载（直接删文件夹）<br>大恒、海康、Basler 等工业相机 SDK 都爱这里 |
| **从源码编译安装**        | OpenCV 源码、一些开源项目 make install         | ~/下载（源码压缩包）                  | 默认也去 **/usr/local/**<br>（可指定 --prefix=/usr/local） | 想最新版或自定义时用<br>和手动 .run 一样去 /usr/local |
| **Snap 包安装**           | `snap install vscode`                          | Snap 系统自动管理                     | /snap/ 或 /var/lib/snapd/                               | Ubuntu 推的通用包<br>独立沙箱，位置特殊 |
| **Flatpak 安装**          | `flatpak install org.opencv.OpenCV`            | Flatpak 系统自动管理                  | /var/lib/flatpak/                                       | 跨发行版包管理，位置隔离 |
| **系统镜像 / 工具烧录**   | 树莓派 OS、Ubuntu 镜像 .img/.iso               | ~/下载                                | 不安装到电脑，直接烧录到 SD 卡/U盘                      | 只临时占用下载空间 |

## 4.常见位置速查表

| 位置                               | 放什么类型的东西                          | 典型例子                              | 查看命令 |
|------------------------------------|-------------------------------------------|---------------------------------------|----------|
| **~/下载** 或 **~/桌面**           | 你浏览器手动下载的原始文件                | 大恒 .run 文件、树莓派 .img、源码包   | `ls ~/下载` |
| **/var/cache/apt/archives/**      | apt 下载的 .deb 包（临时）                | OpenCV 等 apt 软件的安装包            | `ls /var/cache/apt/archives/` |
| **/usr/bin/ /usr/lib/**           | apt 安装的软件（系统级）                  | OpenCV 的 opencv_version、库文件      | `ls /usr/bin/opencv*` |
| **/usr/local/**                   | 手动安装的完整软件/SDK                    | 大恒 Galaxy_camera 整个文件夹、库     | `ls /usr/local/` |
| **/usr/local/lib/**               | 手动安装的库文件                          | libgxiapi.so（大恒核心库）            | `ls /usr/local/lib/libgxi*` |
| **/usr/local/bin/**               | 手动安装的可执行程序                      | 某些 SDK 的查看器                     | `ls /usr/local/bin/` |
| **/snap/** 或 **/var/lib/snapd/** | Snap 安装的软件                           | VS Code、Postman 等                   | `snap list` |
| **/var/lib/flatpak/**             | Flatpak 安装的软件                        | 某些跨平台软件                        | `flatpak list` |

## 小贴士
- **apt 安装的**：位置分散在 /usr/，你不用找，直接用就行。想清理临时下载：`sudo apt clean`
- **手动安装的**：原始文件在 ~/下载，安装后去 /usr/local/（推荐位置！不干扰系统）
- **永远别把东西下到 /usr/lib/ 手动**（除非你知道自己在干嘛），容易和系统冲突
- 以后下载大文件统一放 ~/下载，安装完原始包可以删掉省空间
