# Colang

> 目标

静态无类型，支持顶层结构，数据类型包括boolean,int,double,string.

不需要声明变量，类ruby，以函数作为作用域[参考JS]。

if,else,elsif,不允许悬空else,强制要求书写{},方便归约。

实现字符串的垃圾回收[引用计数]

> run

make -f Makefile