〇、前提
因为没有找到完整的、从头到尾的、从起源到未来的介绍嵌入式的资料或网站，所以自己开始写一点文档，或者说是wiki，希望能有人和我一起规划和更新这份文档。

一、嵌入式定义
嵌入式：嵌入到各种设备中执行专项任务的计算机软硬件；通常不包含可以执行各种任务，以计算机原本的功能为主体的设备。
嵌入式设备举例：广告机、电视机、机顶盒、洗衣机、冰箱、红绿灯、门禁、扫码、体温枪……
非嵌入式计算机举例：笔记本、台式机、服务器、工作站、计算机集群、手机。

二、嵌入式分类
不带系统：51单片机、ARM(STM32等)、FPGA(Xlinx)
带简单rtos系统：ARM、DSP(TI)
带MMU和复杂系统：ARM(i.MX等)+Linux
学习嵌入式软件时可以只在上述三类中选一项学习，然后只从事相关类型的工作

嵌入式硬件：
嵌入式软件：

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
