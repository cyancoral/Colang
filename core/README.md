# Colang

> 目标

静态无类型，支持顶层结构，数据类型包括boolean,int,double,string.

不需要声明变量，类ruby，以函数作为作用域[参考JS]。

if,else,elsif,不允许悬空else,强制要求书写{}

Colang支持C语言调用

实现垃圾回收

translation_unit
一个.cpp文件（在将其包含的h文件展开后）就形成一个编译单元
因为编译器是将.cpp文件逐个编译
得到一个个.obj文件（或.o等，具体随编译器而异）
然后将obj链接，生成可执行文件。