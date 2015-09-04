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

typedef enum {
	BOOLEAN_EXPRESSION = 1,
	INT_EXPRESSION,
	DOUBLE_EXPRESSION,
	IDENTIFIER_EXPRESSION,
	ADD_EXPRESSION,
	SUB_EXPRESSION,
	MUL_EXPRESSION,
	DIV_EXPRESSION,
	MOD_EXPRESSION,
	EQ_EXPRESSION,
	NE_EXPRESSION,
	GT_EXPRESSION,
	LT_EXPRESSION,
	LE_EXPRESSION,
	LOGICAL_AND_EXPRESSION,
	LOGICAL_OR_EXPRESSION,
	MINUS_EXPRESSION, // 负号
	FUNCTION_CALL_EXPRESSION,
	NULL_EXPRESSION,
	EXPRESSION_TYPE_COUNT_PLUS_1
} ExpressionType;

typedef Expression_tag Expression;

struct Expression_tag {
	ExpressionType type;
	int line_number;
	union {
		CL_Boolean				boolean_value;
		int 					int_value;
		double 					double_value;
		char 					*identifier;
		AssignExpression		assign_expression;
		BinaryExpression		binary_expression;
		Expression 				*minus_expression;
		FunctionCallExpression 	function_call_expression;
	} u;
};


// create.c
Expression *cl_alloc_expression(ExpressionType type);

// string.c
char *cl_create_identifier(char *str);

// util.c
cl_Interpreter *cl_get_current_interpreter(void);