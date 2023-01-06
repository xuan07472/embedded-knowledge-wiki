MJPEG协议简述和JPEG拆分
===

|作者|将狼才鲸|
|---|---|
|创建日期|2022-12-26|

* CSDN阅读地址：[04 MJPEG协议简述和JPEG拆分](https://blog.csdn.net/qq582880551/article/details/128445375)

---

* MJPEG能搜到的资料和源码比较少，我搜了一圈之后都不知道怎么从mjpeg流中拆分出一张张jpeg图片，也不知道MJPEG格式是用什么方式来组织JPEG图片序列的；
  * 后面我读取和分析了mjpeg的二进制文件后才知道，哪有什么格式，mjpeg就是单纯的将一张张jpeg图片的二进制内容连续放在一起而已，所以JPEG原本根式中二进制FFD8~FFD9之间的数据就是一张图片，如果自己写代码切分jpeg图片，简单的按照FFD9FFD8这四个字符划分图片即可；
  * 但因为只知道了图片的切分字符，并不知道一张图片有多大，所以实际要切分时，还是要按JPEG的格式先简单的解析图片的二进制内容，在判断出长度的基础进行一帧切分。
  * 切分的源码参考ffmpeg-n5.1.2\libavcodec\mjpeg_parser.c中的find_frame_end()函数。
  * ffmpeg相关的源码: mjpeg_parser.c  mjpeg2jpeg_bsf.c

* 其它参考网址： [MJPEG 转JPEG代码](https://blog.csdn.net/JJM152768JJM/article/details/11992229)
