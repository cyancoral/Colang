line_list
	: line
	| line_list line
	;

表示可以多次输入

由于我们是做解释型语言，所以忽略优先级，让C自己完成。

移进/归约

将记号进入并堆积的过程，叫移进。

类似处罚某个规则并进行置换的过程，叫归约。

冲突：

同时可以进行多个归约。

满足移进的规则，同时又满足归约的规则。

移进归约会优先移进，归约归约是致命的，但两个错误都应该避免的。