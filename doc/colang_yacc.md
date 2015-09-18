# 解释语法逻辑

translation_unit
编译单元
一个.c文件(包含.h展开后)形成一个编译单元。
其后可能是其他编译单元或者定义与程序体

definition_or_statement
后跟函数定义或者声明
读到声明的时候获取解释器实体
向变量链添加声明
读到函数定义的时候 function NAME(parameter_list) block
将函数名, 形参列表, 函数体 进行存储
遇到function NAME() block
替换 形参列表 为NULL

形参列表可以但是
IDENTIFIER 
也可以是
IDENTIFIER, IDENTIFIER, IDENTIFIER 

argument_list 

statement_list

expression 

expression_opt

logical_and_expression 

logical_or_expression

equality_expression 

relational_expression

additive_expression 

multiplicative_expression

unary_expression primary_expression

statement

global_statement

if_statement

while_statement

for_statement

return_statement

break_statement

continue_statement

block

elsif

elsif_list

identifier_list

