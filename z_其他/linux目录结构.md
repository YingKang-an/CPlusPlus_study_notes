# <center><font color=orange>Linux目录结构</font></center>
###### 2026.01.01
## **1.Linux路径的描述方式**
- 在linux中，路径层级关系用`/`表示
[![pZNxmgx.md.png](https://s41.ax1x.com/2026/01/01/pZNxmgx.md.png)](https://imgchr.com/i/pZNxmgx)
Linux只有一个顶级目录，叫`根目录`
Windows有多个，即`各个符盘`
- 注意
    - 开头的`/`代表`根目录`
    - 后面的`/`代表`层级关系`

>tree -L 1/
```
.
├── bin -> usr/bin
├── bin.usr-is-merged
├── boot
├── cdrom
├── dev
├── etc
├── home
├── lib -> usr/lib
├── lib64 -> usr/lib64
├── lib.usr-is-merged
├── lost+found
├── media
├── mnt
├── opt
├── proc
├── root
├── run
├── sbin -> usr/sbin
├── sbin.usr-is-merged
├── snap
├── srv
├── swap.img
├── sys
├── tmp
├── usr
└── var
```