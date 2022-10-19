# Lab1 erport

## [练习1]

[练习1.1] 操作系统镜像文件 ucore.img 是如何一步一步生成的?(需要比较详细地解释 Makefile 中每一条相关命令和命令参数的含义,以及说明命令导致的结果)


[练习1.2] 一个被系统认为是符合规范的硬盘主引导扇区的特征是什么?
/tools/sign.c 中
```
    buf[510] = 0x55;
    buf[511] = 0xAA;
```
>下图中最后的"55 AA"即为结束标志，或者称魔数，占扇区最后2字节。每次执行系统引导代码时都会检查MBR主引导扇区最后2字节是否是"55 AA"，若是，则继续执行后续的程序，否则，则认为这是一个无效的MBR引导扇区，停止引导系统。