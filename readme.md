====概述部分

〇、前提
一直想找到一个从头到尾介绍嵌入式知识的网站，就像一般的WiKi网站那样，能够在一个地方就搜索到大部分嵌入式开发要用到的知识，但是并没由找到，所以就自己着手一边搜索资料一边写，想着花个数十年时间应该能搜集到自己想要的资料。希望以后也能遇到有人和我一起规划和更新这份文档，也希望自己不要放弃一直坚持。

前提依赖：汉语、英语：C语言关键字、英文命名、数学：逻辑运算、电脑：键盘布局

一、嵌入式定义
嵌入式：嵌入到各种设备中执行专项任务的计算机软硬件；通常不包含可以执行各种任务（运行各种软件），以计算机原本的功能为主体的设备。
嵌入式设备举例：广告机、电视机、机顶盒、洗衣机、冰箱、红绿灯、门禁、扫码、体温枪……
非嵌入式计算机举例：笔记本、台式机、服务器、工作站、计算机集群、手机。

二、嵌入式分类
不带系统：51单片机、ARM(STM32等)、FPGA(Xilinx等)
带简单rtos系统：ARM、DSP(TI等)
带MMU和复杂系统：ARM(i.MX等)+Linux
学习嵌入式软件时可以只在上述三类中选一项学习，然后只从事相关类型的工作

嵌入式硬件：主控芯片 外设芯片 输入输出 电源
[嵌入式系统硬件组成](https://blog.csdn.net/xiaohongya/article/details/100733863)



嵌入式软件：编译器预设启动代码、boot代码、操作系统+应用或者裸机驱动+应用，以上各个部分中某些模块都有可能由芯片厂商提供，自己可以直接用或者稍做移植。

三、嵌入式特点

四、芯片、模块、平台、行业、产品列表

五、开发方法

六、开发工具

七、芯片架构
嵌入式使用的主控芯片（单片机或者MCU）对应于IC设计中的SoC
运算器 控制器 指令集 协处理器 存储管理 中断和例外管理 缓存 
[CPU芯片逻辑设计技术](https://baike.baidu.com/item/CPU%E8%8A%AF%E7%89%87%E9%80%BB%E8%BE%91%E8%AE%BE%E8%AE%A1%E6%8A%80%E6%9C%AF)
[芯片设计相关基础](https://zhuanlan.zhihu.com/p/431837543)
(有图)FPU ISU FXU IDU IFU LSU L2 LC MC

[芯片设计的起源](https://zhuanlan.zhihu.com/p/104925162)
(有图)指令寄存器 指令解码器 寄存器 PC栈 ALU寄存器 ALU carry

SoC芯片公司

[数字芯片设计入门？](https://www.zhihu.com/question/21892919)
soc硬件架构 低功耗设计 总线架构 接口协议 FIFO 仲裁器 
UART/IIC/SPI/DDR等常用接口协议

[以硬件架构的思维方式看待软件架构（二）](https://zhuanlan.zhihu.com/p/464828478)
硬件架构：SoC RJ45网口 SD 音频IN/OUT HDMI eMMC DDR SATA

[SoC](https://blog.csdn.net/iteye_13202/article/details/82575744)
一个MCU、微CPU或者DSP ROM/flash/EEPROM RAM 时钟源 外设 外部接口 ADC/DAC 电源和电源管理
JTAG ARMCPU 电压调节 IO
系统控制器：高级中断控制 电源管理控制 PLL锁相环 OSC晶振 复位控制 局部电源检测 上电断电控制 定时器 看门狗 调试单元 PID控制
ASB/AHB/APB总线：外设桥 存储控制：EBI SRAM Flash 外设数据控制 Flash编程 应用特殊逻辑 网络MAC 串口 SPI ADC CAN USB PWM 

[SOC常见架构_RISCV AI SOC实战（一，概述及架构设计）](https://blog.csdn.net/weixin_39693101/article/details/109963793)

(有图)AHB APB 计算核心 各种外设

[ARM架构](./arm架构.md)

八、硬件上电流程
[常见SOC启动流程分析](https://blog.csdn.net/weixin_34153893/article/details/93263448)
CPU获取编译器预设的代码，初始化时钟、看门狗、启动介质
执行编译器预设的启动介质初始化代码，读取并执行用户编写的boot代码
引导代码重定位地址并执行用户代码：操作系统+应用，或者裸机程序程序（驱动+应用）

====开发部分

九、软件编程
前提一：C语言
前提二：ARM汇编 or 51汇编 or xtensa汇编 or DSP汇编(HIFI or TI)

十、硬件编程
前提一：verilog(FPGA)

十一、编译原理

十二、操作系统

十三、驱动  
驱动寄存器通用结构：输入输出地址（可与DMA配合）、中断控制  

*本地文档：*[i2s音频模块](./i2s模块.md)  

十四、应用

十五、算法

十六、GUI
