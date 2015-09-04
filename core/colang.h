#include <stdio.h>

struct  CL_Interpreter_tag
{
	MEM_Storage			interpreter_storage;// 解释器存储
	MEM_Storage			execute_storage;	// 运行内存管理
	Variable 			*variable;			// 变量链
	FunctionDefinition	*function_list; 	// 函数链
	StatementList		*statement_list; 	// 语句链表
	int 				line_number; 		// 执行行数
};

// create.c
Expression *cl_alloc_expression(ExpressionType type);

// string.c
char *cl_create_identifier(char *str);

// util.c
cl_Interpreter *cl_get_current_interpreter(void);