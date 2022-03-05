# i2s音频模块  

*参考网址：*  
|序号|网址|内容简述|
|---|---|---|
|1|[音频总线I2S协议：I2S收发模块FPGA的仿真设计](http://www.elecfans.com/d/1309604.html)|介绍i2s的由来|
|2|[I2S音频总线](http://www.360doc.com/content/13/0517/12/496343_286066684.shtml)|详细介绍音频知识|
|3|[I2S_RX 音频接收通用设计](https://www.cnblogs.com/mage0306/p/10595329.html)|I2S模块IC设计|
|4|[I2S音频总线（一）————数字音频技术](https://blog.csdn.net/yangguoyu8023/article/details/72235377)|介绍声音采样原理，此作者的系列文章很好|
|5|[I2S音频总线（二）————I2S总线协议](https://blog.csdn.net/yangguoyu8023/article/details/72235384)|总线细节|
|6|[I2S音频总线（三）————S3C2440的I2S控制器](https://blog.csdn.net/yangguoyu8023/article/details/72235387)|模块寄存器|
|7|[I2S音频总线学习（四）I2S接口设计](http://blog.chinaunix.net/uid-26715658-id-3163268.html)|I2S模块IC设计|
<center>表1 I2S参考网址</center>


## 一、i2s寄存器介绍  

只写软件的话，对i2s模块怎么和ADC/DAC配合，怎么接喇叭和耳机插孔，通讯时序怎么样都不用关心，只需要操作i2sin/i2sout的模块寄存器就可以了。不同芯片的寄存器可能设计的完全不一样，但是都能实现类似的功能。  

i2s模块寄存器很简单，只有几个常规的寄存器：  
|i2s模块寄存器||||
|---|---|---|---|
|控制寄存器|模式寄存器|分频寄存器|地址寄存器|
<center>表2 I2S模块的寄存器</center>  

i2s模块驱动简单，对不同的主控芯片需要写不一样的驱动，只要注意控制中断和及时收发数据就可以了。  

有些芯片的i2s模块是和i2c模块复用的，因为引脚数量和控制方式都类似，但它们两者各自的通讯协议完全不一样。  

## 二、I2S和PCM  
* I2S和PCM协议的异同：  

* I2S是PCM的一个子集，接口定义是一样的，只是左右声道控制信号不一样，实际上数据线上的数据内容是一样的。从时序图可以看出，I2S左右声道分别为高低电平，PCM只有一个起始信号，左声道数据紧跟右声道。其实，I2S传输的数据内容就是PCM。  
*参考网址：* [I2S与pcm的区别](https://www.pianshen.com/article/50871466981/)  
*参考网址：* [PCM和I2S区别](https://blog.csdn.net/haima1998/article/details/78155412)  

* 在音视频中，PCM是一种用数字表示采样模拟信号的方法。  

* 参考网址：* [PCM数据格式介绍](https://blog.csdn.net/qq_25333681/article/details/90682989)  

|缩写|全名|详述|
|---|---|---|
|I2S|Inter-IC Sound Bus，集成电路内置音频总线|飞利浦为传输音频数据制定的总线标准，几乎成了行业标准，三根线，传输的数据格式是PCM|
|PCM|Pulse Code Modulation，脉冲编码调制|飞利浦和索尼公司推出，模拟语音信号经过采样量化以及一定数据排列就是PCM，是数字音频的raw data，未经压缩的音频采样数据裸流|
<center>表3 I2S与PCM缩写解释</center>  

* 描述PCM数据的6个参数：
|参数|描述|
|---|---|
|Sample Rate，采样频率|8kHz(电话)、44.1kHz(CD)、48kHz(DVD)|
|Sample Size，量化位数|通常该值为16-bit|
|Number of Channels，通道个数|常见的音频有立体声(stereo)和单声道(mono)两种类型，立体声包含左声道和右声道。另外还有环绕立体声等其它不太常用的类型|
|Sign，是否是有符号位|表示样本数据是否是有符号位，比如用一字节表示的样本数据，有符号的话表示范围为-128 ~ 127，无符号是0 ~ 255|
|Byte Ordering，字节序|字节序是little-endian还是big-endian。通常均为little-endian。字节序说明见第4节|
|Integer Or Floating Point，整形或浮点型|大多数格式的PCM样本数据使用整形表示，而在一些对精度要求高的应用方面，使用浮点类型表示PCM样本数据|
<center>表4 PCM参数</center>  

## 三、PCM文件的生成与播放  
* 想要生成PCM格式的测试文件可以使用ffmpeg命令行模式，比较方便。  

FFmpeg转PCM命令：  
ffmpeg -i roar.wav -acodec pcm_s16le -f s16le -ac 2 -ar 16000 out.pcm  
输入文件可以是mp3、aac、wav、mp4、mkv等音视频文件。  

FFmpeg播放PCM命令：  
ffplay -ar 16000 -ac 2 -f s16le -i out.pcm   

*参考网址： * [WINDOWS下使用FFMPEG生成PCM音频文件并播放（通过命令的方式）](https://www.freesion.com/article/580069852/)  

* 生成的PCM文件可以用于I2S OUT模块的播放测试，也可以用于MP3 encoder的编码测试。  



