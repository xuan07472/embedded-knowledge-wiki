# 001_url_file_rw：文件读写多合一  
* 读写文件  
* 读写网络流  
* 读写其它……  

---

* origin source，参考源码来源：  
[ffmpeg/libavformat/avio.c](https://gitee.com/mirrors/ffmpeg/blob/master/libavformat/avio.c)  

---

* url支持的类型：  
|tcp|http|udp|https|tls|rtp|file|
|---|---|---|---|---|---|---|
|||||||

URLProtocol->name == file

url.c
file.c

file_open.c
open lseek stat fstat
file.c
read write lseek close opendir readdir closedir 
avio.c
protocols.c
url.c

是否是file本地文件协议，由key value全局配置来决定

url_find_protocol
ffurl_get_protocols

