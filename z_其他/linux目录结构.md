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
## 2. 根目录树
>tree -L 1/
```
.
├── bin -> usr/bin          # 基本命令（链接到 /usr/bin）
├── boot                    # 启动文件（内核、GRUB）
├── dev                     # 设备文件（硬盘、U盘等）
├── etc                     # 配置文件（系统和软件配置）
├── home                    # 用户主目录（你的私人文件）
├── lib -> usr/lib          # 核心库（链接）
├── media                   # 可移动设备自动挂载（U盘）
├── mnt                     # 手动临时挂载点
├── opt                     # 第三方软件（可选安装位置）
├── proc                    # 进程信息（虚拟，实时）
├── root                    # root 用户家目录
├── run                     # 运行时临时数据
├── sbin -> usr/sbin        # 系统管理命令
├── snap                    # Snap 包软件
├── srv                     # 服务数据（网站、FTP）
├── sys                     # 内核设备信息（虚拟）
├── tmp                     # 临时文件（重启清空）
├── usr                     # 用户程序和数据（最大、最重要）
└── var                     # 可变数据（日志、缓存）
```