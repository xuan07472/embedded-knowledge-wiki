用Visual Studio创建底层C程序工程编译会报错，放弃。
用Qt + MSVC创建底层C程序工程编译会报错，放弃。
可以用gcc 直接make编译，我用的是Windows下安装的gcc和make工具（安装这些工具的同时也会自动安装MinGW工具），生成的是exe。
也可以用Qt + MinGW 64-bit（安装Qt时勾选MinGW选项即可，Qt6版本及以上的MinGW只有64位可用了）
Qt创建工程时不能使用Paint C++，只能使用Paint C，因为编译时会报一些C++专有的关键字错误，和类型强制转换不支持等错误。

group_buf_queue_unitest_qt_proj/group_buf_queue_unitest_qt_proj.pro是Qt的工程入口，双击即可打开。
点击编译，在Qt下方的一个“应用程序输出”内嵌窗口中可以看到程序输出。
Qt源码界面上可能出现一些C++相关的报错，但是程序编译时并没有error（实际上也是调用gcc编的，没用C++的东西），只有一些warnning（用gcc直接make时没有这些warnning），能编译通过，程序正常输出结果。