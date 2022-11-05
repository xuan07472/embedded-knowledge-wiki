# 《QEMU默认支持的所有开发板列表》

|作者|日期|
|---|---|
|将狼才鲸|2021-11-12|

b站：[才鲸嵌入式](https://space.bilibili.com/106424039)  
码云：[才鲸](https://gitee.com/langcai1943)  

## 一、背景  
* QEMU官方文档  
[《Welcome to QEMU’s documentation!》](https://www.qemu.org/docs/master/)  

* QEMU支持的开发板详细信息在源码的docs/system下各个文档中  
* 安装git，并 clone qemu代码，代码地址：  
[《Gitee 极速下载 / qemu》](https://gitee.com/mirrors/qemu)  
* QEMU源码中不包含任何开发板的可执行文件，需要针对不同的开发板用不同的编译工具生成可执行文件后再进行测试  

## 二、开发板列表  

QEMU默认支持以下架构的CPU：  

```
   target-arm
   target-avr
   target-m68k
   target-mips
   target-ppc
   target-riscv
   target-rx
   target-s390x
   target-sparc
   target-sparc64
   target-i386
   target-xtensa
```

针对开发板的音视频编解码，显示加速暂不能模拟（要测试音视频可以将代码做成兼容跨平台的，在Linux或者Windows下直接调用硬件编解码器进行测试）。  

以下内容不包含通用设备，只包含特定厂商的某一款特定开发板：  

|开发板|芯片|架构|核心|支持的模块|未实现的模块|编译工具|厂商|行业|
|---|---|---|---|---|---|---|---|---|
|stm32vldiscovery|STM32F100RBT6|arm|Cortex-M3|* ARM Cortex-M3, Cortex M4F<br/> * Analog to Digital Converter (ADC)<br/> * EXTI interrupt<br/> * Serial ports (USART)<br/> * SPI controller<br/> * System configuration (SYSCFG)<br/> * Timer controller (TIMER)|* Camera interface (DCMI)<br/> * Controller Area Network (CAN)<br/> * Cycle Redundancy Check (CRC) calculation unit<br/> * Digital to Analog Converter (DAC)<br/> * DMA controller<br/> * Ethernet controller<br/> * Flash Interface Unit<br/> * GPIO controller<br/> * I2C controller<br/> * Inter-Integrated Sound (I2S) controller<br/> * Power supply configuration (PWR)<br/> * Random Number Generator (RNG)<br/> * Real-Time Clock (RTC) controller<br/> * Reset and Clock Controller (RCC)<br/> * Secure Digital Input/Output (SDIO) interface<br/> * USB OTG<br/> * Watchdog controller (IWDG, WWDG)|Atollic TrueSTUDIO|ST|实验用的小板|
|netduino2|STM32F205RFT6|arm|Cortex-M3|同上|同上|vs2019 + Micro .net Framework SDK + Netduino SDK + **C#语言编程**|ST|类似Arduino|
|netduinoplus2|STM32F405RGT6|arm|Cortex-M4F|同上|同上|同上|ST|同上|
|imx25-pdk|i.MX25|arm|ARM926|- SD controller<br/>- AVIC<br/>- CCM<br/>- GPT<br/>- EPIT timers<br/>- FEC<br/>- RNGC<br/>- I2C<br/>- GPIO controllers<br/>- Watchdog timer<br/>- USB controllers|/|IAR Embedded Workbench for Arm—C/C++ compiler & debugger tools|NXP|消费类和工业类|
|Xilinx Versal Virt|虚拟设备|arm|Cortex-A72 * 2|- Interrupt controller (ARM GICv3)<br/>- 2 UARTs (ARM PL011)<br/>- An RTC (Versal built-in)<br/>- 2 GEMs (Cadence MACB Ethernet MACs)<br/>- 8 ADMA (Xilinx zDMA) channels<br/>- 2 SD Controllers<br/>- OCM (256KB of On Chip Memory)<br/>- XRAM (4MB of on chip Accelerator RAM)<br/>- DDR memory|does not yet model any other devices, including the PL and the AI Engine.|Linux + 交叉编译gcc，或者vivado|Xilinx|ARM+FPGA|
|Cubietech Cubieboard|全志A10|arm|Cortex-A8|- Timer<br/>- UART<br/>- RTC<br/>- EMAC<br/>- SDHCI<br/>- USB controller<br/>- SATA controller|/|sun-java6-jdk，安卓|Cubietech 和全志科技|类似树莓派|
|Orange Pi PC|全志H3|arm|Cortex-A7 * 4|* SMP (Quad Core Cortex-A7)<br/> * Generic Interrupt Controller configuration<br/> * SRAM mappings<br/> * SDRAM controller<br/> * Real Time Clock<br/> * Timer device (re-used from Allwinner A10)<br/> * UART<br/> * SD/MMC storage controller<br/> * EMAC ethernet<br/> * USB 2.0 interfaces<br/> * Clock Control Unit<br/> * System Control module<br/> * Security Identifier device|- Graphical output via HDMI, GPU and/or the Display Engine<br/>- Audio output<br/>- Hardware Watchdog|Linux + 交叉编译gcc|全志科技|类似树莓派|
|Palm Tungsten_E PDA|OMAP310|arm|ARM925T|-  Texas Instruments OMAP310 System-on-chip (ARM925T core)<br/>-  ROM and RAM memories (ROM firmware image can be loaded with<br/>   -option-rom)<br/>-  On-chip **LCD controller**<br/>-  On-chip Real Time Clock<br/>-  TI TSC2102i **touchscreen controller** / analog-digital converter /<br/>   **Audio CODEC,** connected through MicroWire and I2S busses<br/>-  GPIO-connected matrix keypad<br/>-  Secure Digital card connected to OMAP MMC/SD host<br/>-  Three on-chip UARTs||/|TI|电纸书 PDA，带显示和音频解码|
|Raspberry Pi boards|raspi0 raspi1ap raspi2b raspi3ap raspi3b|arm|ARM1176JZF-S Cortex-A7 Cortex-A53|* ARM1176JZF-S, Cortex-A7 or Cortex-A53 CPU<br/> * Interrupt controller<br/> * DMA controller<br/> * Clock and reset controller (CPRMAN)<br/> * System Timer<br/> * GPIO controller<br/> * Serial ports (BCM2835 AUX - 16550 based - and PL011)<br/> * Random Number Generator (RNG)<br/> * Frame Buffer<br/> * USB host (USBH)<br/> * GPIO controller<br/> * SD/MMC host controller<br/> * SoC thermal sensor<br/> * USB2 host controller (DWC2 and MPHI)<br/> * MailBox controller (MBOX)<br/> * VideoCore firmware (property)|* Peripheral SPI controller (SPI)<br/> * Analog to Digital Converter (ADC)<br/> * Pulse Width Modulation (PWM)|/|树莓派|微型电脑|
|Arm Realview boards|realview-eb realview-eb-mpcore realview-pb-a8 realview-pbx-a9|arm|/|-  ARM926E, ARM1136, ARM11MPCore, Cortex-A8 or Cortex-A9 MPCore CPU<br/><br/>-  Arm AMBA Generic/Distributed Interrupt Controller<br/><br/>-  Four PL011 UARTs<br/><br/>-  SMC 91c111 or SMSC LAN9118 Ethernet adapter<br/><br/>-  **PL110 LCD controller**<br/><br/>-  PL050 KMI with PS/2 **keyboard and mouse**<br/><br/>-  PCI host bridge<br/><br/>-  PCI OHCI USB controller<br/><br/>-  LSI53C895A PCI SCSI Host Bus Adapter with hard disk and CD-ROM<br/>   devices<br/><br/>-  PL181 MultiMedia Card Interface with SD card.|/| RealView MDK，Linux                                          |ARM|arm官方开发板|
|Boundary Devices SABRE Lite|i.MX6|arm|/|* Up to 4 Cortex-A9 cores<br/> * Generic Interrupt Controller<br/> * 1 Clock Controller Module<br/> * 1 System Reset Controller<br/> * 5 UARTs<br/> * 2 EPIC timers<br/> * 1 GPT timer<br/> * 2 Watchdog timers<br/> * 1 FEC Ethernet controller<br/> * 3 I2C controllers<br/> * 7 GPIO controllers<br/> * 4 SDHC storage controllers<br/> * 4 USB 2.0 host controllers<br/> * 5 ECSPI controllers<br/> * 1 SST 25VF016B flash|/|Linux|NXP, 飞思卡尔|/|
|Siemens SX1|OMAP310|arm|ARM925T|-  Texas Instruments OMAP310 System-on-chip (ARM925T core)<br/><br/>-  ROM and RAM memories (ROM firmware image can be loaded with<br/>   -pflash) V1 1 Flash of 16MB and 1 Flash of 8MB V2 1 Flash of 32MB<br/><br/>-  **On-chip LCD controller**<br/><br/>-  On-chip Real Time Clock<br/><br/>-  Secure Digital card connected to OMAP MMC/SD host<br/><br/>-  Three on-chip UARTs|/|/|TI|/|
||||||||||

还有大概一半的设备，因为芯片不常用或者和嵌入式无关，我就没有列出来了，感兴趣的直接去qemu源码docs/system/目录中的文档进行翻阅  

qemu的仿真主循环位于cpu-exec.c:cpu_exec函数中  

[qemu源码分析](https://www.cnblogs.com/long123king/p/3584053.html)  
[【系列分享】QEMU内存虚拟化源码分析](https://www.anquanke.com/post/id/86412)  
[QEMU源码分析系列(二)](http://blog.chinaunix.net/uid-8679615-id-5710883.html)  
