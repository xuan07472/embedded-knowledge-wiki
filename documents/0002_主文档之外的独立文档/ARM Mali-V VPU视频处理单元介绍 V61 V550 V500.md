## 《ARM Mali-V VPU视频处理单元介绍 V61 V550 V500》

|作者|张靖|
|---|---|
|日期|2022-01-13|

### 一、名词解释：  
+ Mali：
一系列显示GPU及其子模块IP（IP为芯片中的术语，一组集成电路模块），隶属于ARM。有一个显示处理事业部专门研发Mali系列的IP。  

### 二、相关资料：  
*备注：ARM官网上找不到任何V系列视频处理器IP的资料。*  

Mali至少有四种类型：  
* 一种是图形处理器GPU，支持通用显卡API，型号如早期纯数字系列、中期T系列、后期G系列。  
* 一种是图像信号处理的C系列。  
* 一种是网上不公开资料的显示控制器DP系列。  
* 一种是网上不公开资料的视频处理器VPU，供芯片原厂购买的V系列（如V500、V550、V61），提供MVE接口，只进行视频编解码，不进行图形处理。  

---

本文档只描述Mali V系列VPU，不涉及GPU及其它。  
ARM Mali VPU IP相关的文档和代码，需要从ARM获取。  

### 三、Mali-V资料描述  

获取到的资料：只有mali_v550.tar.gz  
初始化期间MVE（例如Mali V550）需要运行一个ARM私有的固件.fwb（如：h264dec.fwb hevcdec.fwb jpegdec.fwb mpeg2dec.fwb mpeg4dec.fwb rvdec.fwb vc1dec.fwb vp8dec.fwb jpegenc.fwb h264enc.fwb hevcenc.fwb vp8enc.fwb）  
这些固件是无法修改的，只能原样发给MVE模块运行。  
ARM会提供驱动的示例代码，来提供驱动API用于操作MVE进行编码或解码，但缺少完整的demo（例如miniplayer源码就是integration_kit；但不包含从存储介质中获取h264文件，使用MVE解码后送到显示模块显示的功能，而只是一个MVE驱动）。  

#### 1、文件夹分类：
* mali_v550\v2：嵌入式异步驱动源码integration_kit（miniplayer），MVE架构文档、Mali-V550简要介绍文档，Mali固件，工具（Linux下的程序mve_decode32），Mali-V固件。   
* mali_v550\v1：安卓和Linux驱动源码mali_video，驱动编译与测试文档，Mali-V固件。   

#### 2、资料中的内容：  

|Directory|Description|
|---|---|
|documentation/ |包含Errata, Release Notes, User Guide, and Host Interface Specification文档|
|integration_kit/ |miniplayer源码（也是mve驱动的源码，嵌入式中操作mve就裁剪这里面的代码）|
|integration_kit/boot/ |boot an ARM processor的源代码，主要是汇编.|
|integration_kit/build/ |编译用的一些配置|
|integration_kit/src/ |miniplayer（也是mve驱动）源码|
|integration_kit/bin/ |编译后的输出文件夹|
|integration_kit/obj/ |编译时的object files存放位置|
|streams/ |miniplayer能用的几个流文件|
|model/ |mve_decode and mve_encode工具|
|firmware/ |MVE固件，不可更改，每次编码解码都需要加载固件|

---

|Deliverable Part Number|Description|
|---|---|
|VD304K03A-DC-10002-r4p0-00rel0|Mali Android Video SW Integration Guide|
|VD304K03A-DC-06002-r4p0-00rel0|Mali Android Video SW Release Note (this document)|
|VD304K03A-SW-98001-r4p0-00rel0|Mali Android Video SW Integration Kit|
|VD304K03A-SW-98002-r4p0-00rel0|GPLv2 Mali Android SW Device DSC|

* 有用的文档：  
《MVE-Host-Interface-Specification-v2.pdf》：MVE Host Interface Specification (Protocol v2.0)：Mali-V工作原理和操作接口相关，重要！  
《Mali-V550-Firmware-Tools-User-Guide.pdf》：ARM® Mali™-V61 Firmware Tools User Guide：获取到的资料种类介绍  
《Mali_Android_Video_SW_DDK_Integration_Guide_And_Codec_User_Manual.pdf》：ARM® Mali™ Video Processor Android DDK Integration Manual：编译与运行相关，使用通用的OpenMAX接口  

* 用不上的文档：  
  《Mali_V550_Firmware_Errata_Core.pdf》：Mali V550 Firmware Product Errata Notice  
  《Mali_V550_Firmware_Release_Notes.pdf》：Mali-V550 Firmware Release Notes  
  《Mali-V550-Firmware-Model-Release-Notes.pdf》：Mali-V550 Firmware Release Notes  
  《Mali-V550-Firmware-Model-Errata.pdf》：Mali V550 Firmware Product Errata Notice  
  《Mali_Android_Video_SW_DDK_Errata.pdf》：Mali Android Video SW DDK Product Errata Notice  
  《Mali_Android_Video_SW_DDK_Release_Notes.pdf》：Mali Android Video SW DDK Release Notes  

* 相关的工具：  
firmware tools：

|mve_encode/mve_decode|Linux下桌面环境yuv到264编码，264到yuv解码；会调用miniplayer；mve_decode更像是一个播放器，但可惜并未公开源码|
|---|---|
|Miniplayer|有源码；别被名字误导，这并不是一个播放器demo，而只是一个MVE驱动，实际上mve_encode or mve_decode会使用miniplayer|

#### 3、缺少的内容：  
• ARM® Mali™-V550 Video Processor Integration Manual (ARM 100107).  
• ARM® Mali™-V550 Video Processor Configuration and Sign-off Guide (ARM 100106).  
• ARM® Mali™-V550 Video Processor Technical Reference Guide (ARM 100105).  
• ARM® Mali™-V61 Video Processor Technical Overview (ARM 100503)   
• ARM® Mali™-V61 Video Processor Technical Reference Manual (ARM 100504)  
• ARM® Mali™-V61 Video Processor Configuration and Integration Manual (ARM 100505)  

#### 4、参考网址：  
* [Mali维基百科](https://wiwiki.kfd.me/wiki/Mali_(GPU))  
* [Mali GPUs for Graphics Processing](https://www.arm.com/products/silicon-ip-multimedia)  
* [Mali-V61](https://www.arm.com/search#q=V61)  
* [Mali-V550](https://www.arm.com/search#q=V550)  
* [Mali-V500](https://www.arm.com/search#q=V550)  
* [Graphics and Gaming Development](https://developer.arm.com/solutions/graphics-and-gaming)  
* [V550](https://developer.arm.com/documentation/100964/1116/Fast-Models-components/Media-components/V550?lang=en)  
* [V61](https://developer.arm.com/documentation/100964/1116/Fast-Models-components/Media-components/V61?lang=en)  
* [Open Source Mali Video Kernel Device Driver](https://developer.arm.com/tools-and-software/graphics-and-gaming/mali-drivers/video-drivers)  

### 四、MVE工作原理：  

资料：《MVE-Host-Interface-Specification-v2.pdf》：MVE Host Interface Specification  
资料中只说了MVE操作需要的所有messages命令，没有完整的流程介绍。熟悉整个流程还是需要看懂源码。    

* 每个流的编码或者解码过程都是一个session，要为每个session分配必要的内存。  
* 使用job和state来控制session的运行。  
* state：PAGETABLE FIRMWARE BITBUFS FRAMEBUF MSG_INQ MSG_OUTQ BUF_INQ BUF_INRQ BUF_OUTQ BUF_OUTRQ INTBUFS RPC_BUF  
* session工作期间会使用Queue传递各种消息。  
* 异步通讯操作job message，使用message queues，同步通讯使用RPC。  
* 每个session（一段编码或者解码）包含：页表、固件、状态、缓存。  
* mali的地址需要和实际内存地址进行映射。  
* 所需要的内存可以按支持的画幅大小进行裁剪配置。  
* 相关的消息格式为MVE_REQUEST_CODE_xxx、MVE_RESPONSE_CODE_xxx、MVE_BUFFER_BITSTREAM_FLAG_xxx  
* miniplayer是在mve_decode之下运行的，mve_decode提供了视频流的编码和解码，但是没有源码。miniplayer只是一个mve驱动。  
* mve_encode可以输入.264，解码后输出.yuv。  
* mve_decode可以输入.yuv，编码后输出.264。  



### Mali-V模块操作流程：  

驱动源码：miniplayer(integration_kit)  

* 驱动和MVE固件通过寄存器沟通，可以读写32位寄存器。  
* 驱动中需要添加内存和resize内存。  
* 需要mve_decode生成的g_session_dump > src/session_dump.c来配合操作，是一系列操作的集合；outfile.mvedump？。  
* 



