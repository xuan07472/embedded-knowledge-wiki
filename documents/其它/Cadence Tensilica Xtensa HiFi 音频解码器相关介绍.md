## 《Cadence Tensilica Xtensa HiFi 音频解码器相关介绍》  

|作者|将狼才鲸|
|---|---|
|日期|2022-01-13|

### Cadence HiFi名词解释：Cadence Tensilica HiFi DSP架构，用于音频解码。  

- Tensilica：嵌入式处理器公司，已被芯片EDA巨头Cadence收购  
- Xtensa：DSP处理器核心，也是该系列的型号名称，也是该处理器中指令集架构的名称  
- HiFi：特指32位音频/语音处理数字信号处理 (DSP) 核，基于 Xtensa® 架构  

### Cadence提供的两个文件夹：  
“xa_hifi3_l32r_LE5_mp3_dec_lib_3_xxx.tgz”和“xa_hifi3_l32r_LE5_aacmchplus_v2_loas_dec_lib_3_xxx.tgz”（网上没有，需从Cadence获取）  
文件夹中包含：  
* 1、mp3和aac解码静态库：xa_mp3_dec.a和xa_aacmchplus_v2_loas_dec.a，无法更改，只能直接使用音频解码功能  
* 2、API头文件  
* 3、应用demo  
* 4、操作文档：《HiFi-MP3-DecoderProgrammersGuide.pdf》和《HiFi-AAC-DecoderProgrammersGuide.pdf》  

*这个项目由Cadence在2006年第一次发布，并一直在持续迭代*  

### 参考资料：  
[用于音频、声音、语音和人工智能的 Tensilica HiFi DSP](https://www.cadence.com/zh_CN/home/tools/ip/tensilica-ip/hifi-dsps.html)  
[Tensilica HiFi 5 DSP](https://www.cadence.com/zh_CN/home/training/all-courses/86262.html)  
[Tensilica Audio Codec API](https://www.cadence.com/zh_CN/home/training/all-courses/86049.html)  

### 其它内容  
影响音视频前/后处理性能的FFT（快速傅氏变换），FIR（有限脉冲响应）和IIR（无限脉冲响应）算法函数库在HiFi3 DSP上的性能提高了80%  
[Tensilica HiFi 3 DSP将音频后处理和语音处理性能提高了1.5倍多](http://www.eepw.com.cn/article/128147.htm)  
[《Tensilica HiFi DSP Family.pdf》](https://www.cadence.com/content/dam/cadence-www/global/en_US/documents/ip/tensilica-processor-ip/hifi-dsps-ds.pdf)  
[HiFi 3 DSP](https://www.cadence.com/zh_CN/home/tools/ip/tensilica-ip/hifi-dsps/hifi-3.html)  
Cadence xa_dec音频编码源码，文件名以xa开头，有13个文件。并且这些源码没有其它限制，任何人都可以拷贝、复制、传播这些源码。  

Tensilica DSP的编码没有官方库和源码，使用了Jean-Georges Fritsch(C-Cube Microsystems)的开源代码。  

[HiFi DSPs come with a comprehensive software suite](https://www.cadence.com/en_US/home/tools/ip/tensilica-ip/hifi-dsps/software.html)  
[Tensilica Introduces 24-bit Xtensa HiFi Audio Engine; Speeds Addition of Audio Support to Chip Designs](https://ip.cadence.com/news/93/330/Tensilica-Introduces-24-bit-Xtensa-HiFi-Audio-Engine-Speeds-Addition-of-Audio-Support-to-Chip-Designs)  
