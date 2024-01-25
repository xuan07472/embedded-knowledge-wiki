《Cadence Tensilica Xtensa HiFi 音频编解码器、Xplorer开发环境相关介绍》  
===

|作者|将狼才鲸|
|---|---|
|创建日期|2022-01-13|
|修改日期|2023-06-27|

## 一、介绍

### 1、Cadence HiFi名词解释：Cadence Tensilica HiFi DSP架构，用于音频编解码。  

- Tensilica：嵌入式处理器公司，已被芯片EDA巨头Cadence收购  
- Xtensa：DSP处理器核心，也是该系列的型号名称，也是该处理器中指令集架构的名称  
- HiFi：特指32位音频/语音处理数字信号处理 (DSP) 核，基于 Xtensa® 架构  

### 2、Cadence提供的两个解码文件夹：  
“xa_hifi3_l32r_LE5_mp3_dec_lib_3_xxx.tgz”和“xa_hifi3_l32r_LE5_aacmchplus_v2_loas_dec_lib_3_xxx.tgz”（网上没有，需从Cadence获取）  
文件夹中包含：  
* 1、mp3和aac解码静态库：xa_mp3_dec.a和xa_aacmchplus_v2_loas_dec.a，无法更改，只能直接使用音频解码功能  
* 2、API头文件  
* 3、应用demo  
* 4、操作文档：《HiFi-MP3-DecoderProgrammersGuide.pdf》和《HiFi-AAC-DecoderProgrammersGuide.pdf》  

*这个项目由Cadence在2006年第一次发布，并一直在持续迭代*  

* 参考资料：  
[用于音频、声音、语音和人工智能的 Tensilica HiFi DSP](https://www.cadence.com/zh_CN/home/tools/ip/tensilica-ip/hifi-dsps.html)  
[Tensilica HiFi 5 DSP](https://www.cadence.com/zh_CN/home/training/all-courses/86262.html)  
[Tensilica Audio Codec API](https://www.cadence.com/zh_CN/home/training/all-courses/86049.html)  

* 其它内容  
影响音视频前/后处理性能的FFT（快速傅氏变换），FIR（有限脉冲响应）和IIR（无限脉冲响应）算法函数库在HiFi3 DSP上的性能提高了80%  
[Tensilica HiFi 3 DSP将音频后处理和语音处理性能提高了1.5倍多](http://www.eepw.com.cn/article/128147.htm)  
[《Tensilica HiFi DSP Family.pdf》](https://www.cadence.com/content/dam/cadence-www/global/en_US/documents/ip/tensilica-processor-ip/hifi-dsps-ds.pdf)  
[HiFi 3 DSP](https://www.cadence.com/zh_CN/home/tools/ip/tensilica-ip/hifi-dsps/hifi-3.html)  
Cadence xa_dec音频编码源码，文件名以xa开头，有13个文件。并且这些源码没有其它限制，任何人都可以拷贝、复制、传播这些源码。  

Tensilica DSP的编码没有官方库和源码，使用了Jean-Georges Fritsch(C-Cube Microsystems)的开源代码。  

[HiFi DSPs come with a comprehensive software suite](https://www.cadence.com/en_US/home/tools/ip/tensilica-ip/hifi-dsps/software.html)  
[Tensilica Introduces 24-bit Xtensa HiFi Audio Engine; Speeds Addition of Audio Support to Chip Designs](https://ip.cadence.com/news/93/330/Tensilica-Introduces-24-bit-Xtensa-HiFi-Audio-Engine-Speeds-Addition-of-Audio-Support-to-Chip-Designs)  

### 3、Xplorer IDE开发软件

* Cadence会提供一个软件安装包“Xtensa_Xplorer_RI”，以及向其购买的许可证“Xtensa_Xplorer_license”，软件在Windows下运行，Xplorer软件是基于开源IDE软件Eclipse的。
* 软件的安装程序在软件包的Xtensa_Xplorer_RI-20xx.x\RI-20xx.x\tools\Xplorer-x.x.xx-windows-installer.exe

### 4、Tensilica HiFi的文档

* Tensilica HiFi的文档在Xtensa_Xplorer_RI-20xx.x\RI-20xx.x\docs\目录下
  * Xtensa的各个CPU的寄存器介绍、指令集介绍、底层库介绍、XOS实时操作系统介绍的文档都在里面，例如《HiFi5_ug.pdf》、《inst_set_sim_ug.pdf》、《isa_rm.pdf》、《OSKit_guide.pdf》、《programmers_guide.pdf》、《visionq7_ug.pdf》、《xos_rm.pdf》、《xtensa_lx7_data_book.pdf》、《xtensa_opencl_sdk_ug.pdf》、《xtensa_xcc_compiler_ug.pdf》

* DSP的优势在于处理整形、定点、浮点乘法指令很快，单个指令周期可以处理多条浮点型乘加指令，比CPU快很多，还有变长霍夫曼编解码指令，快速傅里叶变换则通过乘加操作才实现；各种音频处理的算法都是基于乘加指令来完成，但是算法包也是收费的。

### 5、常用指令介绍

* HIFI3支持单条指令周期内4个16x16bit定点或整形操作，支持单条指令周期内2个标准浮点型乘加操作。
* AE_SA16X4_IP  ae_f16x4   