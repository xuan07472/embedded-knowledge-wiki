# 嵌入式知识图谱WiKi  

---

|作者|将狼才鲸|
|---|---|
|创建时间|2022-02-18|

---

*Gitee文档源文件仓库网址* [ 才鲸 / 嵌入式知识图谱WiKi](https://gitee.com/langcai1943/embedded-knowledge-wiki)  
*CSDN有图的文档阅读网址* [嵌入式知识图谱WiKi](https://blog.csdn.net/qq582880551/article/details/123013592)  
*Bilibili视频讲解网址（待完成）* [才鲸嵌入式主页](https://space.bilibili.com/106424039)  

---

## 一、概述  

### 1）模块框图  

*备注：gitee暂不支持mermaid框图和流程图显示。可以下载本git仓库并用Typora等软件打开本.md文件查看。*  
*也可以点击[该CSDN同名文章](https://blog.csdn.net/qq582880551/article/details/123013592)查看能正常显示图片的版本。*  

*备注：因为mermaid subgraph对框图的自定义布局不支持，所以这里用 -.- 虚线来控制布局。*  

---

<center>图1 嵌入式框图</center>  

```mermaid
graph TB
subgraph 硬件
    subgraph 主控芯片
        subgraph MCU/SoC
        end

        subgraph DSP
        end

        subgraph FPGA
        end

        MCU/SoC -.- DSP -.- FPGA
    end

    subgraph 外设芯片及配套电路
    end

    subgraph 电源电路
    end

    subgraph 时钟电路
    end

    外设芯片及配套电路 -.- 电源电路 -.- 时钟电路

    subgraph 复位电路
    end

    subgraph 通道与接口

    end

    subgraph PCB布线
    end

    复位电路 -.- 通道与接口 -.- PCB布线
end

PCB布线 -.- boot

subgraph 软件
    subgraph 裸机驱动+应用
        subgraph 芯片开发包
        end

        subgraph 用户编写的代码
        end

        芯片开发包 -.- 用户编写的代码
    end

    subgraph 操作系统+驱动+应用
        subgraph 原厂操作系统+驱动
        end

        subgraph 驱动移植
        end

        subgraph 用户应用
        end

    原厂操作系统+驱动 -.- 驱动移植 -.- 用户应用
    end

    subgraph boot
    end

    subgraph 算法
    end

    subgraph API接口
    end

    subgraph 架构
    end

    boot -.- 算法 -.- API接口 -.- 架构
end

架构 -.- C语言:boot+驱动+应用+算法

subgraph 工具
    subgraph IDE/编译器
        subgraph 编译器预设初始化代码
        end

        subgraph 编译原理
        end

        编译器预设初始化代码 -.- 编译原理

        subgraph 优化选项
        end

        subgraph 调试与发布
        end

        优化选项 -.- 调试与发布
    end

    subgraph 开发语言
        subgraph C语言:boot+驱动+应用+算法
        end

        subgraph C++:应用+算法+GUI
        end

        subgraph 汇编:boot+算法
        end

        subgraph Verilog:FPGA
        end

        subgraph Matlab:算法
        end

        C语言:boot+驱动+应用+算法 -.- C++:应用+算法+GUI -.- 汇编:boot+算法

        Verilog:FPGA -.- Matlab:算法
    end
end
```

---

### 2）知识依赖（各方向学习路线流程图待补充）  

#### 1. 前提依赖（提前劝退）  
+ 1.1 **汉语听说**：学汉字的前提；  

家庭言传身教；  

+ 1.1 **汉字**：阅读理工科类知识；  

*哔哩哔哩拼音启蒙视频网址：* [语文拼音绘本课](https://www.bilibili.com/video/BV1ZJ411m7f5)  
*哔哩哔哩汉字启蒙视频网址：* [学前班幼儿园幼小衔接学习识字3-6岁认字动画入门视频启蒙早教程](https://www.bilibili.com/video/BV1yE411f7hP)  
~~学校对应的课程：语文（小学、初中）~~  

+ 1.2 **行业英语**：编程语言关键字、变量命名、函数命名、写部分英文注释、写部分英文文档、阅读只有英文版的芯片资料、协议资料、算法资料、行业资料、源码注释、源码函数名和变量名；  

*哔哩哔哩英文字母歌视频网址：* [ABC song 经典英文字母歌](https://www.bilibili.com/video/BV1BZ4y1T7i1)  
*哔哩哔哩英语音标视频网址1：* [【48个英文音标的示范读音】音标应该怎么读？](https://www.bilibili.com/video/BV17b411c7A7)  
*哔哩哔哩英语音标视频网址2：* [（纯干货）英语音标教学- YouTube](https://www.bilibili.com/video/BV1Ks41187ev)  
*哔哩哔哩英语单词视频网址1：* [1节课刷完高考英语3500单词（绿色护眼乱序版）](https://www.bilibili.com/video/BV1NK4y147Wo)  
*哔哩哔哩英语单词视频网址2：* [第1季合集：英语单词速记--刷爆英语1000词](https://www.bilibili.com/video/BV1JN411R7wW)  
~~学校对应的课程：英语（初中、高中）~~  

+ 1.3 **数学**：逻辑运算（布尔运算）、算术运算表达式（加减乘除余）、十六进制、二进制、十进制；  

~~学校对应的课程：数学（小学、初中、高中），数字电路（大学）~~  

+ 1.4 **电脑**：键盘布局、拼音或五笔、开机关机、装软件、卸载软件、Linux操作系统高级使用（可选）、计算器使用、写Word/Markdown文档、画Excel表格（可选）、写PPT汇报（可选）、画Visio流程图与框图（可选）、画XMind思维导图（可选）；  

~~学校对应课程：信息技术（小学、初中）~~  

+ 1.5 **计算机（可选，不影响初次入职）**：操作系统概念（可选）、中断、线程（可选）；  

~~学校对应课程：操作系统原理（大学）~~  

+ 1.6 **视力**（精度可选）：单元测试时要看的LED灯珠（色盲回避）、屏幕显示的UI（可选，色盲色弱回避）；  

+ 1.7 **上肢**：双手健全（键盘打字、快捷键的使用）；  

+ 1.8 **学历与专业**（可选）：看老板态度；  

学校相关专业：  
计算机科学与技术、电子信息科学与技术、微电子学、测控技术与仪器、数学与应用数学、信息与计算科学、信息工程、物理学、 应用物理学、机械设计制造及其自动化、机械工程及自动化、自动化、电子信息工程、通信工程、电子科学与技术、生物医学工程、其它特定行业相关专业如飞行器设计工程、探测制导与控制技术等（本科）  

电子信息工程技术、应用电子技术、微电子技术、嵌入式技术与应用、电子电路设计与工艺、物联网应用技术、物联网工程技术、计算机应用技术、软件技术、智能产品开发、通信技术、机械制造与自动化、数控技术、电机与电器技术、机电一体化技术、工业过程自动化技术、工业自动化仪表、工业机器人技术、汽车电子技术等（专科）  

*备注：计算机相关专业并不占优势（竞争专业过多）*  

*参考网址：* [普通高等学校本科专业目录](http://www.cdgdc.edu.cn/xwyyjsjyxx/xwsytjxx/265591.shtml)  
*参考网址：* [普通高等学校高等职业教育（专科）专业目录（2015年）](https://baike.baidu.com/item/%E6%99%AE%E9%80%9A%E9%AB%98%E7%AD%89%E5%AD%A6%E6%A0%A1%E9%AB%98%E7%AD%89%E8%81%8C%E4%B8%9A%E6%95%99%E8%82%B2%EF%BC%88%E4%B8%93%E7%A7%91%EF%BC%89%E4%B8%93%E4%B8%9A%E7%9B%AE%E5%BD%95%EF%BC%882015%E5%B9%B4%EF%BC%89)  

#### 2. 不同方向的入门（首次入职）  
2.1 51单片机（软硬件）  
2.2 硬件  
2.3 电源（纹波、低功耗）  
2.4 功放（匹配）  
2.5 STM32等单片机驱动（裸机）  
2.6 STM32等单片机应用（裸机）  
2.7 RTOS移植和驱动（ARM、DSP等）  
2.8 RTOS应用（ARM、DSP等）  
2.9 FPGA（Verilog、数电）  
2.10 Linux移植（U-Boot、根文件系统）  
2.11 Linux字符驱动  
2.12 Linux块驱动  
2.13 Linux应用  
2.14 通讯算法（调制解调、Matlab、DSP、汇编、C、数学）  
2.15 编解码算法（音视频等）  

---

#### 3 进阶（高级工程师、管理）  
3.1 硬件部门管理  
3.2 软件部门管理  
3.3 51单片机硬件+软件+行业应用+GUI（可选）+架构  
3.4 硬件+电源+功放+量产  
3.5 STM32等单片机驱动+行业应用+架构+通讯协议+GUI（可选）+硬件选型+FPGA（可选）  
3.6 RTOS移植+驱动+行业应用+架构+通讯协议+GUI（可选）+硬件选型+FPGA（可选）  
3.7 Linux移植+字符驱动+块驱动+杂项驱动+通讯协议+硬件选型+FPGA（可选）  
3.8 Linux行业应用+架构+GUI（可选）  
3.9 DSP+调制解调+编解码+人工智能算法   
3.10 不同行业多年经验（与上述岗位相结合）  

|音视频|GUI|通讯|人工智能|物联网|汽车|金融|医疗|机械|激光|电力|机器人|
|---|---|---|---|---|---|---|---|---|---|---|---|
|白色家电|黑色家电|玩具|芯片原厂|显示|航空航天|工业设备|军工|轨道交通|光电|仪器仪表|电机电控|
|通信|传感器|执行器|安防|自动化|生物|||||||

<center>表1 跳槽时（非第一份工作）需要的特定行业经验</center>  
*备注：所以入行需谨慎，第一份工作非常重要，决定你以后很多年的工作走向，除非想转行从零开始*  

*参考网址* [行业研究数据库](https://www.hanghangcha.com/)  
*参考网址* [软件和信息技术服务业行业分类图(嵌入式系统软件行业) ](https://wenku.baidu.com/view/ab9412ad2ec58bd63186bceb19e8b8f67d1cef34.html)  

### 3）写作背景  

* 一直想找一个从头到尾介绍嵌入式的网站，就像一般的WiKi网站那样，能够在一个地方就搜到大部分的嵌入式开发知识，但是又没找到，所以我就自己尝试着写，想着花个数十年时间应该能搜集到想要的资料。希望以后也有人和我一起规划和更新这份文档，也希望自己能一直坚持。  

#### 1. 嵌入式定义  
+ **嵌入式**：嵌入到各种设备中执行专项任务的计算机软硬件；通常不包含可以执行多种不确定任务（运行各种软件），以计算机原本的功能为主体的设备。  
+ **嵌入式设备**举例：广告机、电视机、机顶盒、洗衣机、冰箱、红绿灯、门禁、扫码、体温枪……  
+ **非嵌入式计算机**举例：笔记本、台式机、服务器、工作站、计算机集群、手机（应用类）。  

## 二、各个模块  
### 1）硬件设计   
*详细内容未涉及……*  

#### 1. 硬件架构框图  

* 普通硬件设计是围绕着主控芯片及其配套的驱动模块来进行的。  
* 下图是一个典型的硬件框图，包含芯片最小系统、电源模块、各个外设接口。  

<center>图2 硬件框图举例</center>  

![avatar](https://gitee.com/langcai1943/embedded-knowledge-wiki/raw/develop/documents/T2_%E7%A1%AC%E4%BB%B6%E6%A1%86%E5%9B%BE.jpeg)  

*参考网址：* [基于ARM与μClinux的RTU设计](http://gongkong.gongye360.com/paper_view.html?id=266814)  

#### 2. 硬件设计流程  

此处忽略外观设计和结构设计。  
设计流程为：器件选型、原理图设计、PCB设计、输出PCB及BOM表、PCB贴片及验证、软硬件联调。  

*参考网址：* [嵌入式系统硬件组成](https://blog.csdn.net/xiaohongya/article/details/100733863)  
*参考网址：* [一个完备的嵌入式系统硬件架构有哪几部分构成？](https://blog.csdn.net/weibo1230123/article/details/80206223)  
*参考网址：* [嵌入式系统基本概念(硬件篇)](https://blog.csdn.net/qq_36717753/article/details/90582307)  
*参考网址：* [以硬件架构的思维方式看待软件架构（二）](https://zhuanlan.zhihu.com/p/464828478)  

---

### 2）集成电路（IC）设计（扩展内容，可不翻阅）  
#### 1. SoC（主控芯片）设计  
##### 1.1 SoC架构  
* 嵌入式使用的主控芯片（单片机或者MCU）对应于IC设计中的SoC。  

<center>图3 典型的SoC芯片模块图</center>  

![avatar](https://gitee.com/langcai1943/embedded-knowledge-wiki/raw/develop/documents/T3-SoC%E6%9E%B6%E6%9E%84.png)  

*参考网址：* [SoC架构](https://blog.csdn.net/weixin_39060517/article/details/113619888)  
*参考网址：* [SoC](https://blog.csdn.net/iteye_13202/article/details/82575744)  

架构图解析：  

* SoC（包括MCU、DSP或者单片机芯片）的主要框架就是**AHB总线**、**APB总线**和总线上的**模块**（CPU与外设等）。  

* AHB和APB都是ARM公司出品的基于IP开发的SoC系统集成总线，它们一个高速一个低速，其实功能就和USB等总线协议类似，可以接入和控制多个设备（模块）。  

*参考网址：* [AHB百度百科](https://baike.baidu.com/item/AHB)  
*参考网址：* [AHB总线协议](https://blog.csdn.net/ivy_reny/article/details/78144785)  
*参考网址：* [SOC常见架构_RISCV AI SOC实战（一，概述及架构设计）](https://blog.csdn.net/weixin_39693101/article/details/109963793)  
*参考网址：* [SoC知识及选型经验分享](https://blog.csdn.net/lijiuyangzilsc/article/details/46535913)  

|缩写|全名及解释|详情|
|---|---|---|
|SoC|System on Chip，系统级芯片，也称片上系统| 一种专用目标的集成电路，将微处理器、模拟IP核、数字IP核（包含各种驱动模块）和存储器(或片外存储控制接口)集成在单一芯片上；具体的产品有：MCU、单片机、DSP、手机CPU |
|AHB|Advanced High performance Bus，高级高性能总线|ARM出品，几乎已经成了行业标准；主要用于芯片内部高性能模块(如CPU、DMA、DSP、ROM、RAM、USB、网络)之间的连接，同样也连接APB低速总线的主控接口Bridge；多主多从设计，有的模块既做主也做从（如DMA）|
|Bridge|APB桥|APB总线架构不像AHB支持多个主模块，在APB里面唯一的主模块就是APB 桥|
|APB|Advanced Peripheral Bus，高级外围总线|主要用于低带宽的周边外设之间的连接，例如UART、SPI、I2C|
|CPU|Central Processing Unit，中央处理器|计算机系统的运算和控制核心，处理指令、执行操作、控制时间、处理数据；数字电路中各种逻辑运算、算数运算、控制的操作接口都是一条指令，指令要转换成特定数字电路模块的入口，所以CPU的工作分为以下5个阶段：取指令、指令译码、执行指令、访存取数和结果写回；主要包括两个部分，即控制器、运算器，其中还包括高速缓冲存储器及实现它们之间联系的数据、控制的总线|
|DMA|Direct Memory Access，直接存储器访问|不依赖CPU将一块数据从一个地址空间复制到另一个地址空间，大量节省CPU时间|
|Flash|Flash EEPROM，闪存|是ROM；有两种：NORFlash和NANDFlash；结合了ROM和RAM的长处，不仅具备电子可擦除可编程（EEPROM）的性能，还可以快速读取数据（NVRAM的优势）|
|SRAM|Static Random-Access Memory，静态随机存取存储器|不需要刷新电路即能保存它内部存储的数据，断电后丢失；速度快但贵一点，也用作高速缓存|
|DDR|Double Data Rate SDRAM，双倍速率同步动态随机存储器|具有双倍数据传输率的SDRAM，其数据传输速度为系统时钟频率的两倍，DDR是一个时钟周期内可传输两次数据，也就是在时钟的上升期和下降期各传输一次数据|
|SD|Secure Digital Memory Card|基于闪存的存储卡，驱动方式为SDIO|
|USB|Universal Serial Bus，通用串行总线|一种高速串行总线，兼容性好速度快|
|WDT|Watchdog Timer，看门狗|是一个定时器电路，一般有一个输入，叫喂狗，一个输出到MCU的RST端，MCU正常工作的时候，每隔一段时间输出一个信号到喂狗端，给WDT清零，如果超过规定的时间不喂狗，（一般在程序跑飞时），WDT定时超过，就会给出一个复位信号到MCU，使MCU复位，防止MCU死机|
|Timer|定时器|定时到了之后给出中断|
|GPIO|General-purpose input/output，通用型输入输出|引脚可以用于输入、输出或其他特殊功能|
|UART|Universal Asynchronous Receiver/Transmitter，异步收发传输器|通用串行数据总线，用于异步通信，对应的电气协议有RS-232/RS-422/RS-485，其中485是半双工|
|I2C|Inter-Integrated Circuit，内置集成电路总线|一种简单、双向二线制同步串行总线|
|SPI|Serial Peripheral Interface，串行外设接口|一种高速的，全双工，同步的通信总线，使用四根线|
|System Controller|系统控制|电源、复位、锁相环频率等|
|其它专用驱动模块||模块非常多，一个人总是只能精通里面的很少一部分|

<center>表2 SoC芯片模块英文缩写名词解释</center>  

* 除了电源管理、射频处理等少数几个功能外，SOC几乎包办了其它所有硬件功能。  

##### 1.2 CPU（处理器核）  

* CPU最重要的特点就是把所有的操作融合成了一种操作方式：指令集。  

<center>图4 典型的CPU内模块框图</center>  

![avatar](https://gitee.com/langcai1943/embedded-knowledge-wiki/raw/develop/documents/T4_CPU%E7%BB%93%E6%9E%841.png)  


| 模块 | 子模块 | 描述 |
| ---- | ------ | ---- |
| 操作接口 | 指令集、IO接口 | 对CPU的所有操作都通过指令集中的指令和数据来完成 |
| 总线 | 数据总线DBUS、指令总线IBUS、控制总线 | CPU与外界，CPU内指令、数据、译码器、寄存器、算术单元之间的数据通讯 |
| 运算器 | ALU算术单元、FPU浮点单元 | 计算机之所以叫计算机的由来，核心结构是计算 |
| 控制器 | 译码器、JTAG、流水线生成、中断 | 将指令集中的指令转换成实际的操作，和返回操作的结果 |
| Cache缓存 | 指令缓存、数据缓存 | 缓存用于提高速率 |
<center>表3 CPU内主要模块和子模块</center>  

*参考网址：* [深度分析国产龙芯新架构CPU：自主当崛起](https://www.eetop.cn/view-50164.html) 英文框图  
*参考网址：* [微处理器分类及主要技术性能](https://mbb.eet-china.com/blog/3658169-370989.html) 中文原理框图  
*参考网址：* [微处理器微计算机微处理机单片机cpu区别](https://zhidao.baidu.com/question/424009835054682252.html) 有中文框图  
*参考网址：* [计算机组成原理——CPU](https://blog.csdn.net/include_zrl/article/details/112382253) 有中文的简单框图  
*参考网址：* [cpu的结构(CPU的结构与工作原理)](http://www.chenmo.net.cn/998794) 有Cortex-A8的简单框图  
*参考网址：* [cpu架构一](https://blog.csdn.net/sinat_38259539/article/details/84627610) 有中文的CPU结构图  
*参考网址：* [微架构](https://baike.baidu.com/item/%E5%BE%AE%E6%9E%B6%E6%9E%84) 里面的结构图最详细  
*参考网址：* [CPU芯片逻辑设计技术](https://baike.baidu.com/item/CPU%E8%8A%AF%E7%89%87%E9%80%BB%E8%BE%91%E8%AE%BE%E8%AE%A1%E6%8A%80%E6%9C%AF)：CPU设计的基础教程  
*参考网址：* [芯片设计相关基础](https://zhuanlan.zhihu.com/p/431837543)：有奔腾简单的版图与模块框图  
*参考网址：* [芯片设计的起源](https://zhuanlan.zhihu.com/p/104925162)：有一张简单的Intel4004版图与模块框图  

###### **1.2.1 C51核指令集**  

* C51（8051）的指令并不多，并且比较简单。  
* 8051单片机共有111条指令，按指令功能分，可分为数据传送类29条，算术运算类24条，逻辑运算类24条，位操作类12条，控制转移类22条。  
* 指令寻址方式共7种，分别是：立即数寻址，直接寻址，寄存器寻址，寄存器间接寻址，变址寻址，相对寻址，位寻址。  

* 详细指令内容详见 *参考网址：* [8051汇编指令集](https://blog.csdn.net/u010835747/article/details/119993636)  

*参考网址：* [单片机8051指令集](https://blog.csdn.net/qq_45653763/article/details/107906583)  
*参考网址：* [8051汇编指令](https://www.cnblogs.com/techecho/p/9809662.html)  
*参考网址：* [8051单片机共有多少条指令？](https://zhidao.baidu.com/question/566536288494065644.html)  

* 汇编通过地址跳转即可以实现各种条件判断和循环功能，如if else switch do while for等高级语言的功能。  
* 通过压栈和弹栈的指令即可以各种函数的调用。  

###### **1.2.2 ARM核指令集**  

* ARM核各个系列的介绍详见 *参考网址：* [关于ARM的内核架构](https://www.cnblogs.com/zhugeanran/p/8431127.html)  

* ARM 可以用两套指令集：ARM指令集和Thumb指令集。  

*参考网址：* [ARM汇编指令集汇总](https://blog.csdn.net/qq_40531974/article/details/83897559)  
*参考网址：* [ARM指令集](https://blog.csdn.net/weixin_42110547/article/details/86672824)  
*参考网址：* [关于ARM处理器指令集](https://blog.csdn.net/qq_45385706/article/details/108478867)  
*参考网址：* [ARM指令集](https://www.diangon.com/m209371.html)  
*参考网址：* [Arm Architecture Reference Manual for A-profile architecture](https://developer.arm.com/documentation/ddi0487/ha/?lang=en) 文档下载  

**1.2.3 TI DSP指令集**  

包含C66x、C67x等型号，有各种加速运算的指令。  

*参考网址：* [KeyStone C66x CorePac Instruction Set Architecture](https://training.ti.com/sites/default/files/docs/instruction-set-architecture-presentation.pdf)  
*参考网址：* [MS320C674x DSP CPU and Instruction Set Reference Guide](https://www.ti.com/lit/ug/sprufe8b/sprufe8b.pdf) Chapter 3 Instruction Set  
*参考网址：* [C66x-CorePac用户指南---中文版](https://wenku.baidu.com/view/866eee93de88d0d233d4b14e852458fb770b38dd.html) TI C66x DSP寄存器介绍  
*参考网址：* [TMS3205000系列DSP汇编语言程序设计](https://baike.baidu.com/item/TMS3205000%E7%B3%BB%E5%88%97DSP%E6%B1%87%E7%BC%96%E8%AF%AD%E8%A8%80%E7%A8%8B%E5%BA%8F%E8%AE%BE%E8%AE%A1)  

**1.2.4 Cadence Xtensa HiFi DSP指令集**  
详见 <u>**子文档**</u>：《[XtensaHifiDsp.md](https://gitee.com/langcai1943/embedded-knowledge-wiki/blob/develop/documents/2.2.2_1.2.4_XtensaHifiDsp.md)》  

**1.2.5 Xilinx FPGA**  
*参考网址：* [Welcome to the Xilinx Wiki!](https://xilinx-wiki.atlassian.net/wiki/spaces/A/overview)  

#### 2. 数字IC设计  

数字IC设计使用硬件描述语言Verilog，设计时要有时序、并行、延时的思想。  
芯片设计可以分为两部分，前端和后端，仿真也可以分为前仿和后仿。  

*参考网址：* [数字芯片设计入门？](https://www.zhihu.com/question/21892919)  
*参考网址：* [SoC芯片龙头有哪些，SoC芯片概念股一览](http://www.southmoney.com/gupiao/glg/202202/23494806.html)  
*参考网址：* [数字IC设计流程介绍](https://zhuanlan.zhihu.com/p/260933238)  
*参考网址：* [前仿真与后仿真](https://blog.csdn.net/zhangyujie0316/article/details/106360591)  
*参考网址：* [数字IC设计流程及工具简介](https://blog.csdn.net/weixin_39269366/article/details/120665925)  

#### 3. 模拟IC设计  

模拟IC设计需要画原理图和版图。  

*参考网址：* [模拟集成电路设计流程（1）——熟悉Cadence环境](https://zhuanlan.zhihu.com/p/344938075)  
*参考网址：* [模拟集成电路设计流程（2）——原理图设计与仿真](https://zhuanlan.zhihu.com/p/344939731)  
*参考网址：* [模拟集成电路设计流程（3）——不同的电路仿真方法](https://zhuanlan.zhihu.com/p/344937484)  
*参考网址：* [模拟集成电路设计流程（4）——版图设计基础](https://zhuanlan.zhihu.com/p/350617982)  
*参考网址：* [模拟集成电路设计流程（5）——版图验证](https://zhuanlan.zhihu.com/p/350813971)  
*参考网址：* [模拟芯片/IC设计，都经历过哪些lesson—learned（经验教训）？](https://www.zhihu.com/question/46956546)  
*参考网址：* [怎样学好模拟集成电路设计？](https://www.zhihu.com/question/25911879)  

---

### 3）软件开发  

* 进行一个新项目时，先想好文件夹结构和其中的各个模块，如：  
arch 独立出来的硬件相关的内容（arch下也有drivers、fs、kernel、lib、mm、usr文件夹，实现这个模块中的硬件相关功能）  
drivers 设备驱动（里面是抽象的接口，不包含实际硬件寄存器的操作）  
fs 文件系统（可选）  
kernel 进程调度（可选）  
lib 通用中间件、基础模块  
mm 内存管理（可选）  
usr 工具类应用  

*参考网址：*  
[Linux内核 -- 内核源码结构](https://www.cnblogs.com/y4247464/p/12333955.html)  
[eCos教程2：eCos源码结构分析](http://velep.com/archives/970.html)  
[RT-Thread / rt-thread](https://gitee.com/rtthread/rt-thread)  
[FreeRTOS介绍与源码结构分析](https://zhuanlan.zhihu.com/p/145699420)  
[uCOS-II源码下载及源码目录结构](https://blog.csdn.net/qq_29344757/article/details/77096149)  

#### 1. boot  
**硬件上电流程**  
* 前提：一般嵌入式硬件都有内部IROM、内部IRAM、外部ROM、外部RAM。  
* 在boot前，启动介质中已经烧录或者拷贝了可执行程序。  

* 一般boot分四步：  

1、芯片上电后判断启动介质（启动介质的选择由几个芯片引脚的电平排序来决定，开发时使用跳线，生产则固定启动介质），直接执行ROM启动介质的0地址上的代码，或者将ROM启动介质的0地址及以后的代码拷贝到内部RAM中执行（最开始的启动代码会初始化芯片：如设置CPU频率、关看门狗、关MMU、分类临时内存执行一部分代码、设置异常向量、初始化内存控制器、初始化DDR、分配中断、确定内存资源范围、建立内存空间的映射表、IO端口资源、定义第二步boot入口地址；这部分源码往往由芯片厂商提供的与IDE配套的芯片配置包或者芯片厂商提供的交叉编译器中自带模板；这部分代码是汇编写的）。  

2、与第一步同时，芯片也接收JTAG指令（JTAG执行时不需要ROM中的初始化代码，芯片直接接收并执行JTAG总线上的机器指令序列，这些序列中包含了最开始的芯片初始化机器指令序列），JTAG可以用来加载程序、烧录程序、运行并调试程序。JTAG中的初始化指令序列也由芯片厂商提供的IDE芯片配置包中自带。JTAG需要使用仿真器（如J-Link）。  

3、调用并运行第二阶段初始化代码（第二阶段代码可以从Flash、SD卡、USB、串口、网口等介质中引导）；拷贝第二阶段代码到RAM、初始化堆栈、跳转到RAM运行第二阶段程序，第二阶段程序可以是U-Boot主体，也可以是裸机程序，main函数入口也在第二段初始化代码中，接着会初始化驱动。  

4、如果有操作系统，由U-Boot或者其它的bootloader引导操作系统。  

*参考网址：* [IMX6 uboot的启动流程](https://www.cnblogs.com/cyc2009/p/4077430.html)  
*参考网址：* [TMS320F280025的BOOT流程](https://blog.csdn.net/booksyhay/article/details/120172063)  
*参考网址：* [BOOT流程](https://blog.csdn.net/sp612422/article/details/51730053)  
*参考网址：* [常见SOC启动流程分析](https://blog.csdn.net/weixin_34153893/article/details/93263448)  
*参考网址：* [bootloader(xboot)起动流程分析](http://blog.chinaunix.net/uid-2630593-id-2955923.html)  
*参考网址：* [详解嵌入式系统Boot-Loader](https://blog.csdn.net/liangzc1124/article/details/110180693)  
*参考网址：* [嵌入式u-boot浅析](https://blog.csdn.net/xiaoqiang2080/article/details/77894379)  

#### 2. 系统移植  

<center>图5 操作系统框架</center>  

![avatar](https://gitee.com/langcai1943/embedded-knowledge-wiki/raw/develop/documents/T5_%E6%93%8D%E4%BD%9C%E7%B3%BB%E7%BB%9F%E6%A1%86%E6%9E%B6.jpg)  

* 操作系统包含以下几个主模块：进程管理（线程）、内存管理、文件系统、设备驱动、网络管理（可选）  

|主模块|子模块|描述|
|---|---|---|
|进程管理|TASK、进程或线程创建、挂起、运行、销毁，优先级管理，进程调度，自旋锁，互斥锁，信号量，条件变量，事件，邮箱，管道，Socket套接字，读写锁，共享内存|PV操作，原子操作，同步与互斥，临界资源|
|内存管理|物理地址、虚拟地址、内存映射、分页、命中、内存清理|MMU，实现malloc()、free()|
|文件系统|block块，窗口命中，写块，擦除块| DMA，缓存，volatile关键字|
|驱动|字符驱动、块驱动、杂项驱动、网络驱动|主设备号，子设备号，通用接口，ioctl|
|其它|中断处理、异常处理|ISR和DSR，上半部和下半部，定时器|

<center>表4 操作系统框架</center>  

*参考网址：* [操作系统包含哪些子系统？](https://www.zhihu.com/question/453246529)  
*参考网址：* [Linux 进程与线程的同步与互斥](https://www.cnblogs.com/hzhida/archive/2012/11/01/2750216.html)  

2.1 uCOS（μC/OS）  
2.2 eCos  
2.3 RT-Thread  
2.4 SYS/BIOS（TI）  
2.5 Atomthreads  
2.6 FreeRTOS  
2.7 ThreadX（Cadence Tensilica）  
2.8 VxWorks  
2.9 Linux（U-Boot、kernel、根文件系统）  

**2.10 根文件系统**  

* 如果是Linux可以BusyBox工具来创建根文件系统。  

**2.10.1 Ramfs**  
Ramfs是LinusTorvalds开发的一种基于内存的文件系统，工作于虚拟文件系统(VFS)层，不能格式化，可以创建多个，在创建时可以指定其能使用的内存大小。(实际上，VFS本质上可看成一种内存文件系统，它统一了文件在内核中的表示方式，并对磁盘文件系统进行缓冲。)  

**2.10.2 Ramdisk**  
和网吧一样，用户保存的数据在断电后会丢失，防止入侵和用户乱改乱删文件导致嵌入式设备变板砖。  
Ramdisk是将一部分固定大小的内存当作分区来使用。它并非一个实际的文件系统，而是一种将实际的文件系统装入内存的机制，并且可以作为根文件系统。将一些经常被访问而又不会更改的文件（如只读的根文件系统）通过Ramdisk放在内存中，可以明显地提高系统的性能。  

2.10.3 ext4  
Linux中使用  

2.10.4 FAT32  
兼容U盘、SD卡等经常要在Windows使用的存储设备。  

2.10.5 jffs2  

*参考网址：* [什么是嵌入式的根文件?嵌入式的根文件系统有哪些?](http://www.gec-edu.org/gsnews/show/571664.html)  
*参考网址：*[嵌入式系统中常用的文件系统](https://www.cnblogs.com/wmate/p/13558773.html)  
*参考网址：*[嵌入式 Linux根文件系统移植（三）——根文件系统构建](http://www.360doc.com/content/18/1224/14/8335678_804124205.shtml)  

#### 3. 驱动框架  
驱动寄存器通用结构：输入输出地址（可与DMA配合）、中断控制  

3.1 裸机驱动架构  
4.1 RTOS驱动架构  
4.1.1 uCos  
4.1.2 eCos  
4.1.3 RT-Thread  
……  
4.1.x Linux驱动架构  

#### 4. 驱动模块  
4.1 通讯类驱动  
4.1.1 串口  
4.1.1.1 裸机开发  
4.1.1.2 RTOS开发  
4.1.1.3 Linux开发  

4.1.2 I2C  
4.1.3 SPI  
4.1.4 网络  
4.1.5 USB  
4.1.6 蓝牙  
4.1.7 CAN  
4.1.8 ZigBee  
4.1.9 ModBus  
4.1.10 I2S  

**i2s音频模块**详见 <u>**子文档**</u>：《[i2s模块.md](https://gitee.com/langcai1943/embedded-knowledge-wiki/blob/develop/documents/2.3.4_4.1.10_i2s%E6%A8%A1%E5%9D%97.md)》  

4.2 存储类驱动  
4.2.1 DDR  
4.2.2 Flash  
4.2.3 EEPROM  
……  

4.3 传感器、执行器类驱动  

4.4 行业相关驱动  
4.4.1 键盘  
4.4.2 鼠标  
4.4.3 智能卡  
4.4.4 PCMCIA  
4.4.5 门禁  
4.4.6 水浸  
4.4.7 温度  
4.4.8 破窗  
4.4.9 电能  
4.4.10 计量  
4.4.11 LED  
4.4.12 触摸屏  
4.4.13 显示  
4.4.14 MIPI  
4.4.15 PWM  
4.4.16 i2s音频  
4.4.17 ADC/DAC音频  
4.4.18 振镜  
4.4.19 激光器  
4.4.20 换能器（水声） 
4.4.21 电机   

4.5 杂项驱动  

#### 5. 软件架构（应用框架）  
##### 5.1 模块统一接口  

* 备注：用Visual Studio和Qt + MSVC编译偏底层的C程序会报错（如使用了typeof等GNU C特性时），推荐使用Qt + MinGW 64-bit 或者 gcc编译。  
* 备注：Windows下也可以安装gcc和make（安装此软件时同时也会后台安装MinGW环境），然后可以直接在Windows命令行cmd中执行make生成exe。  
* 备注：Qt + MinGW创建工程时不能使用Paint C++，只能使用Paint C，因为编译时会报一些C++专有的关键字错误（如new关键字），和部分类型强制转换不支持等错误。  

* 1、自行实现的 **“通用模块”** 源码：[点击此处查看源码](https://gitee.com/langcai1943/embedded-knowledge-wiki/tree/develop/source/lib/module_core)  
本地路径：嵌入式知识图谱WiKi\source\lib\module_core\   

##### 5.2 缓存结构  

* 1、各种缓存结构：  

基础：指针、链表、内存、数组。  
数据结构基础：表、树、图（多对多）。  
缓冲区/buffer/顺序表/平直缓存/数组/内存指针（malloc）。  
栈/stack：因为是先进后出，也用于函数调用时的压栈，编译器和高级算法中用的多，日常编程基本上不用。  
堆/heap/完全二叉树：方便排序，编译器和算法中常用，日常编程基本上不用。  
环形缓冲区/环形缓存区/循环队列/loop_buffer/ring_buffer/队列/FIFO/Queue：先进先出，满和空。  

*参考网址：*  [什么是队列（队列存储结构）](http://c.biancheng.net/view/3352.html)  
*参考网址：* [链式队列及基本操作（C语言实现）](http://c.biancheng.net/view/3354.html)  
*参考网址：*  [数据结构与算法教程，数据结构C语言版教程！](http://c.biancheng.net/data_structure/)  

分组队列/多级队列/group_buffer/fifo/queue：每个模块都有自己的队列，且不同队列间可直接通过数据指针无消耗转移大块数据。  

* 2、自行实现的 **“多级缓存队列”模块** 源码：[点击此处查看源码](https://gitee.com/langcai1943/embedded-knowledge-wiki/tree/develop/source/lib/group_buf_queue)  
本地路径：嵌入式知识图谱WiKi\source\lib\group_buf_queue\   

有gcc-makefile和Qt两个工程都能编过，带详细注释和单元测试用例。  

目录结构：  

```
jim@DESKTOP-SVP3BEM MINGW64 /d/3_doc/嵌入式知识图谱WiKi/source/lib/group_buf_queue (develop)
$ tree
.
|-- Makefile
|-- arch_buffer_config.c
|-- arch_buffer_config.h
|-- group_buf_queue.c
|-- group_buf_queue.h
|-- group_buf_queue_init.c
|-- group_buf_queue_init.h
|-- group_buf_queue_unitest.c
|-- group_buf_queue_unitest_qt_proj
|   `-- group_buf_queue_unitest_qt_proj.pro
|-- list.h
|-- module_buf_queue.c
|-- pair_list.c
|-- pair_list.h
`-- readme.txt

1 directory, 15 files
```

* 3、实现原理：  

……待编写……  

5.3 状态机  
状态机用于多任务、多线程、循环中反复执行的函数中进行状态切换  

5.4 循环、TASK、定时器  
5.5 多线程、同步与竞争  

#### 6. 通用应用  
##### 6.1 应用框架  

#### 7. 行业相关应用  
##### 7.1 GUI框架  
###### 7.1.1 Qt编程  
**Qt编程**详见 <u>**子文档**</u>：《[从零开始学习Qt GUI编程](https://gitee.com/langcai1943/qt_gui_simple2complex)》 内容非常全，含各种源码  

###### 7.1.2 uC/GUI  

##### 7.2 多媒体框架  
###### 7.2.1 Linux、Windows、安卓多媒体框架  

详见 <u>**子文档**</u>：《[2.3_7.2.3_不同操作系统多媒体框架.md](./documents/2.3_7.2.1_不同操作系统多媒体框架.md)》  

###### 7.2.2 嵌入式多媒体（音视频API）  
- **音视频**是指：  
a) 音频播放和录制：mp3、aac、ac3、wav（未编码的裸流）、pcm（未编码的裸流）  
b) 音视频播放和录制：mp4、mkv、flv、ts（音视频封装），h264、h265(hevc)、vp8、vp9（纯视频流）
c) 图片显示和抓取：jpeg(jpg)、mjpeg、png、jif  

- **音视频基础知识**完整内容详见*子文档*：《[音视频开发](https://gitee.com/langcai1943/audio_video_codec)》 内容全  

音视频编解码的参考源码有ffmpeg。  
- **FFmpeg音视频编解码**完整内容详见 <u>**子文档**</u>：《[ffmpeg源码及架构分析](https://gitee.com/langcai1943/audio_video_codec/blob/develop/2_ffmpeg%E6%9E%B6%E6%9E%84.md)》内容全  

###### 7.2.3 Qt多媒体（音视频，含界面）  
* **Qt多媒体**详见 <u>**子文档**</u>：《[MultiMedia_VideoAudio.md](https://gitee.com/langcai1943/qt_gui_simple2complex/blob/develop/source/003_MultiMedia_VideoAudio/documents/MultiMedia_VideoAudio.md)》 内容全  

* [Qt官方播放器源码（纯应用）](https://gitee.com/langcai1943/qt_gui_simple2complex/blob/develop/source/003_MultiMedia_VideoAudio/003_qt6.2.3_multimedia/documents/003_qt6.2.3_multimedia.md)  

* [嵌入式播放器源码（自行实现编解码、复用解复用）](https://gitee.com/langcai1943/qt_gui_simple2complex/blob/develop/source/003_MultiMedia_VideoAudio/004_audio_video_codec/%E9%9F%B3%E8%A7%86%E9%A2%91%E5%BC%80%E5%8F%91.md)  

7.3 传感器采集与校准  
7.4 电视节目加解扰  
7.5 键盘键值（不同国家布局、不同游戏手柄布局）  
7.6 蓝牙音响  

#### 8. 通用算法  
调制解调  
编解码  
人工智能  

#### 9. 行业相关算法  
8.1 水声  
8.2 激光打标（显示类）  
8.3 通讯  

## 三、工具使用  
### 1）编码语言  
#### 1. C语言  
1.1 编码规范  
1.2 命名规范  
1.3 注释规范  

#### 2. 51汇编  
1 指令集  

#### 3. ARM汇编  

#### 4. TI DSP汇编  

#### 5. Cadence Xtensa汇编（HiFi DSP）  

#### 6. Verilog硬件描述语言  

#### 7. VHDL硬件描述语言  

#### 8. Matlab语言  

#### 9.Makefile语法（扩展内容）  

#### 10.正则表达式（扩展内容）  

#### 11.SQL数据库（扩展内容）  

#### 12. Git语法  

#### 13. Markdown语法（扩展内容）  
详见 <u>**子文档**</u>：《[Markdown语法](https://gitee.com/langcai1943/embedded-knowledge-wiki/blob/develop/documents/3.1.13_Markdown%E8%AF%AD%E6%B3%95.md)》  

### 2）通讯协议  
#### 1. OSI七层协议  
#### 2. 网络  
#### 3. USB  
……  

## 三、理论知识  
### 1）操作系统原理（扩展内容）  
### 2）编译原理（扩展内容）  
### 3）信息论（扩展内容）  
### 4）离散数学  
1. 快速傅里叶变换  

### 5）自动控制  
### 6）数据结构  
### 7）开发方法  
瀑布开发 敏捷开发

### 8）测试方法  
单元测试 集成测试 老化测试 白盒测试 黑盒测试  

## 四、项目实践  
### 4.1 自运行的吃豆人程序  
详见 <u>**子文档**</u>：《[才鲸 / C语言小游戏](https://gitee.com/langcai1943/c-little-game)》  

### 4.2 Linux下视频播放程序  
详见 <u>**子文档**</u>：《[才鲸 / 嵌入式播放器](https://gitee.com/langcai1943/embedded-player)》  

### 4.3 Qt安卓手机群控PC软件  
详见 <u>**子文档**</u>：《[才鲸 / qtscrcpy_tc_安卓手机群控](https://gitee.com/langcai1943/qtscrcpy_tc)》  

## 五、其它  
待完善……  

### 5.1 嵌入式编程技巧  
详见 <u>**子文档**</u>：《[才鲸 / 嵌入式编程技巧](https://gitee.com/langcai1943/embedded_programming_skills)》  

### 5.2 嵌入式软件笔试题汇总  
详见 <u>**子文档**</u>：《[才鲸 / 嵌入式软件笔试题汇总](https://gitee.com/langcai1943/embedded_exercise_problems)》  

### 5.3 QEMU仿真器（模拟器）  
详见 <u>**子文档**</u>：《[QEMU默认支持的所有开发板列表](https://gitee.com/langcai1943/embedded-knowledge-wiki/blob/develop/documents/0004_QEMU%E6%A8%A1%E6%8B%9F%E5%99%A8_%E4%BB%BF%E7%9C%9F%E5%99%A8/001_QEMU%E9%BB%98%E8%AE%A4%E6%94%AF%E6%8C%81%E7%9A%84%E6%89%80%E6%9C%89%E5%BC%80%E5%8F%91%E6%9D%BF%E5%88%97%E8%A1%A8.md)》  

### 5.4 嵌入式找远程岗位、兼职、和接私单的方法  
详见 <u>**子文档**</u>：《[才鲸 / 嵌入式远程岗位_兼职_私单](https://gitee.com/langcai1943/embedded_remote_work)》  

### 5.5 理工科考证获取额外收入  
详见 <u>**子文档**</u>：《[才鲸 / 专利代理师（仅限理工科）](https://gitee.com/langcai1943/ZhuanDai)》 注：专代很快就要取消，不能考了  

游戏、UI、web前端、web后端、数据库、安卓、iOS、安全、大数据、人工智能、云计算、高级语言：Java，Python，C#、工具类：Json、正则表达式、网络协议栈、XAML、MinGW、MSYS2、Cygwin、Wine兼容层……  

## 六、缩写列表  
待完善……  

## 七、索引（文档地图）  
待完善……  

---

……正在编写中……  

---
