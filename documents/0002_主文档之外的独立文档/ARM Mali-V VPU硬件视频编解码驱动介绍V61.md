ARM Mali-V VPU硬件视频编解码驱动介绍V61 V550
===

|作者|将狼才鲸|
|---|---|
|创建日期|2022-12-13|

CSDN文章地址：[ARM Mali-V VPU硬件视频编解码驱动介绍V61](https://blog.csdn.net/qq582880551/article/details/128303681)

---

## 一、PC上的VPU模拟器和驱动测试

* ARM提供了一个在Linux下运行的VPU模拟器，可以使用模拟器运行Mali-V的驱动程序和Demo，并且能在电脑上看到视频编解码后的效果。
  * 具体查阅的的文档是：ARM® Mali™-V61 Firmware Tools，Revision: r0p1，User Guide，Confidential
  * 相关的文档还有：
  * VPU技术总览：ARM® Mali™-V61 Video Processor Technical Overview (ARM 100503)
  * VPU技术参考手册：ARM® Mali™-V61 Video Processor Technical Reference Manual (ARM 100504)
  * VPU IP配置手册：ARM® Mali™-V61 Video Processor Configuration and Integration Manual (ARM 100505)

* 文档中介绍了VPU模拟器的特性、如何安装、如何编译测试用的驱动源码、如何使用模拟器进行编码和解码

* VPU的工具包包含有：VPU的闭源驱动二进制文件、PC仿真的工具软件（在电脑上用VPU的接口进行编码解码，速度很慢，不能达到实时的编解码速度）、使用VPU调用VPU接口的Demo源码文件，用这个Demo可以编解码一个视频流如H.265、H.264等，但不能播放MP4等有封装格式的多媒体文件，代码中没有解封装、解复用的功能。
  * 编码的PC仿真器名字为mve_encode，是在Linux命令行中运行的软件
  * 解码的PC仿真器名字为mve_decode，是在Linux命令行中运行的软件
  * 描述了怎么在电脑上模拟运行视频流的编码和解码
  * mve_encode和mve_decode模拟器支持的选项有：可以配置B帧的比例、P帧的比例，设置比特率、宏块数、265 264的协议、264使能内部预测、264 cabac、输出NALU格式、缓存大小、Qp值、264 265起始码、垂直镜像、水平镜像；旋转、帧间隔格式。
  * 使用模拟器的VPU驱动的名字叫miniplayer，但是其实只能播264/265裸流。
    * 具体的源码在ARM提供的压缩包内，如：mali_v550\v2\integration_kit\src，源码模块的名字叫mve，这也是我们在单片机中写驱动时主要要参考的源码，Linux或者安卓中写驱动时ARM提供了另外的驱动源码。

## 二、VPU调用的API接口

* 有一个文档描述了Mali VPU MVE视频处理器的工作原理、操作流程：MVE Host Interface Specification (Protocol v2.0)，MPG
* 弄请了ARM VPU的底层API接口，才能直接手写VPU驱动代码，按照项目要求修改驱动；文档中同时也描述了VPU和CPU之间该如何通信，CPU该如何控制VPU
  * CPU和VPU之间通过APB总线通信，使用中断信号和外部共享内存；如果能同时编解码多个视频流，则一个流就是一个session；VPU自带的代码中执行的最小单元是jobs作业，一个作业编解码一帧图片，作业被CPU中执行的驱动所调用

* CPU针对VPU的驱动中，编解码一个视频流时，先创建一个session段，在里面做好内存映射，通常需要几十上百M内存的支持；分配段ID；调用一次job作业来编解码一帧图片
  * 因为VPU需要的内存较多，实际使用中内存也分为了好几页，还有内存映射表
  * VPU将内存划分为：页表映射区域，存放VPU固件程序和状态机，解码输入或编码输出比特流（未解码帧，同样的大小存放的帧数量不同，因为每帧压缩率不一样），核间通信消息队列，输入输出缓存描述队列（每一帧的缓存中可以携带自己独有的信息，如PTS显示时间），VPU自用的内部缓存（占用最多，随视频画幅变大而变大），动态内存申请通知的缓存

* 编解码不同的视频流格式，需要给VPU加载不同的固件二进制文件
  * CPU和VPU之间采用异步通信，不会阻塞，有6个异步消息队列，每个4K大小；使用RPC也可以实现同步通信，这时消息就被阻塞住

* VPU里面有自己的状态机：有停止、运行两个状态
  * 停止状态下要重新从I帧开始编解码
  * VPU固件头的格式在文档中有描述，都是定义一些版本号和地址
  * VPU内存映射表按照4k、4M的页大小进行布局，最大支持4GB总容量的映射
  * CPU驱动中，一个VPU job中可能操作多帧
  * 视频流（例如一部电影）的最后一个输入缓存中需要带有流结束标志，解码后最后输出的一帧同样也带有流结束标志
  * 文档中详细描述了CPU和VPU之间各种job通信的协议细节

* CPU必须调用VPU API的接口，给VPU创建一个内存映射表，将内存映射成VPU需要的从0地址开始的虚拟地址
  * 需要根据画幅进行计算，占用较大的内存有 FRAMEBUF，NTBUFS and BITBUFS
  * VPU输出解码后的帧顺序是PTS显示顺序，而不是DTS比特流解码顺序

* VPU里面列出一些出错码，如果有的帧出现解不了或者马赛克的时候，往往也能收到错误码和dump的出错信息
  * 输入缓存中带了一些帧信息，如：帧间隔格式，一帧数据中是否一定包含一个完整的帧，帧间隔如果是长度的话，采用几字节的长度，子帧结束，帧结束，视频流结束；不同的视频格式支持的帧间隔格式还不一样
  * 输出缓存中的帧信息有：帧结束，是否是参考帧，编码正确
  * 解码时，如果输入的某个缓存是多帧合一，那么输出的缓存也会拆成一帧一个。
  * 已编码的帧大小不好判断，估算时可以按照原始未编码帧大小的1/3来估算
  * 编码时，如果输出SPS PPS VPS信息的话，帧缓存中会带MVE_BUFFER_BITSTREAM_FLAG_CODECONFIG 标签

* 如果跳转时直接只改变输入流的位置，那么会产生马赛克；推荐的方法是先将VPU状态切换到STOP，然后再刷新输入缓存，最后重新切换到运行状态，然后推入新位置的关键帧
  * 编解码器有一定的配置，如：帧间隔信息，编解码协议（简单/基本/高级），忽略流中的配置，内部帧缓存大小，参考帧频率，帧率，NALU格式，帧间隔码，协议级别，一个slice中的宏块数，初始化表，图片解码时的配置
  * 已解码的帧支持不同的格式，YUV420/422，RGB
  * 编解码时支持旋转、缩放、镜像、
  * 文档中给出了不同画幅编解码时需要的最少内存量以及计算公式

* 文档中介绍了跳转和切换文件要做的操作：
  * 先将VPU的状态机从RUNNING切换到STOPPED，不提前切换到STOP状态而直接改变流的话，VPU会进入停顿状态并发出IDLE消息；
  * VPU不支持暂停状态，要想达到暂停的目的，CPU不调用VPU的job就可以实现；
  * VPU切换到STOP状态后，需要执行刷新缓存的job：NPUT_FLUSH, OUTPUT_FLUSH
  * 在停止状态，一些基本的流信息还是保存的，例如尺寸宽高，但是关键帧信息一定会丢失，所以只需要重新输入一个I帧就能继续接着解码，
  * VPU在成功切换到STOP状态后，会发送MVE_RESPONSE_CODE_STATE_CHANGE message给CPU，CPU必须先刷新input buffers，然后再传入新的I帧。
  * VPU切换到STOP状态后，会丢失nput buffers中的内容，但output buffers中的帧会继续保存，因为这些帧所占的时间很短，所以跳转和切换文件时可以不管output的缓存，直接把已解码的帧播完，也可以直接清输出缓存。

## 三、VPU性能和配置

* Mali-V550支持的编码像素格式有：
  * YUV420、NV12、YUV422等，除了V61的编码，都不支持RGB。
  * 详见《MVE-Host-Interface-Specification-v2》7.2 Formats