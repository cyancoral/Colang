#include <stdio.h>
#include "colang_core.h"
#include "colang_developer.h"

#define smaller(a,b) ((a)<(b)?(a):(b))
#define smaller(a,b) ((a)>(b)?(a):(b))

#define MESSAGE_ARGUMENT_MAX (256)
#define LINE_BUFFER_SIZE (1024)

typedef enum {
	PARSE_ERR = 1,					// 解析错误
	CHARACTER_INVALID_ERR,			// 错误字符
	FUNCTION_MULTIPLE_DEFINE_ERR,	// 错误的函数声明
	COMPILE_ERROR_COUNT_PLUS_1		// 编译错误计数
} CompileError;

typedef enum {
	VARIABLE_NOT_FOUND_ERR = 1,			// 未定义变量
	FUNCTION_NOT_FOUND_ERR,				// 未定义函数
	ARGUMENT_TOO_MANY_ERR,				// 参数过多
	ARGUMENT_TOO_FEW_ERR,				// 参数不够
	NOT_BOOLEAN_TYPE_ERR,				// 目标不是boolean型
	MINUS_OPERAND_TYPE_ERR,				// 符号使用错误
	BAD_OPERAND_TYPE_ERR,				// 符号使用错误
	NOT_BOOLEAN_OPERATOR_ERR,			// 符号使用错误
	FOPEN_ARGUMENT_TYPE_ERR,			// 文件读取参数错误
	FCLOSE_ARGUMENT_TYPE_ERR,			// 文件关闭出错
	FGETS_ARGUMENT_TYPE_ERR,			// 获取文件内容错误
	FPUTS_ARGUMENT_TYPE_ERR,			// 打印文件内容错误
	NOT_NULL_OPERATOR_ERR,				// 非NULL操作符
	DIVISION_BY_ZERO_ERR,				// 除0错误
	GLOBAL_VARIABLE_NOT_FOUND_ERR,		// 没有找到全局变量
	GLOBAL_STATEMENT_IN_TOPLEVEL_ERR,	// 全局声明错误
	BAD_OPERATOR_FOR_STRING_ERR,		// string操作符错误
	RUNTIME_ERROR_COUNT_PLUS_1			// 运行错误
} RuntimeError;

typedef enum {
	INT_MESSAGE_ARGUMENT = 1,			// 整型
	DOUBLE_MESSAGE_ARGUMENT,			// 浮点数
	STRING_MESSAGE_ARGUMENT,			// 字符串
	CHARACTER_MESSAGE_ARGUMENT,			// 字符
	POINTER_MESSAGE_ARGUMENT,			// 指针*
	MESSAGE_ARGUMENT_END				// 终结符void
} MessageArgumentType;

typedef struct {
	char *format;
} MessageFormat;

typedef struct Expression_tag Expression;

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

struct StatementList_tag {
	Statement *statement;
	struct StatementList_tag *next;
} StatementList;

typedef struct {
	StatementList *statement_list;
} Block;

struct IdentifierList_tag{
	char *name;
	struct IdentifierList_tag *next;
} IdentifierList;

typedef struct {
	IdentifierList *identifier_list;
} GlobalStatement;

typedef struct Elsif_tag{
	Expression *condition;
	Block *block;
	struct Elsif_tag *next;
} Elsif;

typedef struct {
	Expression  *condition;
	Block	   *then_block;
	Elsif	   *elsif_list;
	Block	   *else_block;
} IfStatement;

typedef struct {
	Expression  *condition;
	Block	   *block;
} WhileStatement;

typedef struct {
	Expression  *init;
	Expression  *condition;
	Expression  *post;
	Block	   *block;
} ForStatement;

typedef struct {
	Expression *return_value;
} ReturnStatement;

typedef enum {
	EXPRESSION_STATEMENT = 1,
	GLOBAL_STATEMENT,
	IF_STATEMENT,
	WHILE_STATEMENT,
	FOR_STATEMENT,
	RETURN_STATEMENT,
	BREAK_STATEMENT,
	CONTINUE_STATEMENT,
	STATEMENT_TYPE_COUNT_PLUS_1
} StatementType;

struct Statement_tag {
	StatementType 		type;
	int 				line_number;
	union {
		Expression 			*expression_s;
		GlobalStatement 	global_s;
		IfStatement 		if_s;
		WhileStatement 		while_s;
		ForStatement 		for_s;
		ReturnStatement 	return_s;
	} u;
};

typedef struct ParameterList_tag {
	char *name;
	struct ParameterList_tag *next;
} ParameterList;

typedef enum {
		COLANG_FUNCTION_DEFINITION = 1,
		NATIVE_FUNCTION_DEFINITION
} FunctionDefinitionType;

typedef struct FunctionDefinition_tag {
	char *name;
	FunctionDefinitionType type;
	union {
		struct {
			ParameterList 	*parameter;
			Block 			*block;
		} colang_f;
		struct	{
			CL_NativeFunctionProc	*proc;
		} native_f;
	} u;
	struct FunctionDefinition_tag	*next;
} FunctionDefinition;

typedef struct Variable_tag {
	char *name;
	CL_Value value;
	struct Variable_tag *next;
} Variable;

typedef enum {
	NORMAL_STATEMENT_RESULT = 1,
	RETURN_STATEMENT_RESULT,
	BREAK_STATEMENT_RESULT,
	CONTINUE_STATEMENT_RESULT,
	STATEMENT_RESULT_TYPE_COUNT_PLUS_1
} StatementResultType;

typedef struct {
	StatementResultType type;
	union {
		CL_Value return_value;
	} u; 
} StatementResult;

typedef struct GlobalVariableRef_tag{
	Variable *variable;
	struct GlobalVariableRef_tag *next;
} GlobalVariableRef;

typedef struct {
	Variable *variable;
	GlobalVariableRef 	*global_variable;
} LocalEnvironment;

struct CL_String_tag {
	int 	ref_count;
	char 	*string;
	CL_Boolean is_literal;
};

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
// 语法解析反馈
void cl_function_define(char *identifier, ParameterList *parameter_list,
						Block *block);

ParameterList *cl_create_parameter(char *identifier);
ParameterList *cl_chain_parameter(ParameterList *list, char *identifier);

ArgumentList *cl_create_argument_list(Expression *expression);
ArgumentList *cl_chain_argument_list(ArgumentList *list, Expression *expr);
StatementList *cl_create_statement_list(Statement *statement);
StatementList *cl_chain_statement_list(StatementList *list, 
										Statement *statement);

Expression *cl_alloc_expression(ExpressionType type);
Expression *cl_create_assign_expression(char *variable,
										Expression *operand);

Expression *cl_create_binary_expression(ExpressionType operator,
										Expression *left,
										Expressino *right);
Expression *cl_create_minus_expression(Expression *operand);
Expression *cl_create_function_call_expression(char *func_name,
												ArgumentList *argument);
Expression *cl_create_identifier_expression(char *identifier);
Expression *cl_create_null_expression(void);
Expression *cl_create_boolean_expression(CL_Boolean value);

Statement *cl_create_global_statement(IdentifierList *identifier_list);
IdentifierList *cl_create_global_identifier(char *identifier);
IdentifierList *cl_chain_indentifier(IdentifierList *identifier_list,
									char *identifier);

Statement *cl_create_if_statement(Expression *condition,
									Block *then_block, Elsif *elsif_list,
									Block *else_block);
Elsif *cl_chain_elsif_list(Elsif *list,Elsif *add);
Elsif *cl_create_elsif(Expression *expr, Block *block);
Statement *cl_create_while_statement(Expression *condition, Block *block);
Statement *cl_create_for_statement(Expression *init,Expression *cond,
									Expression *post,Block *block);

Block *cl_create_block(StatementList *statement_list);
Statement *cl_create_expression_statement(Expression *expression);
Statement *cl_create_return_statement(Expression *expression);
Statement *cl_create_break_statement(void);
Statement *cl_create_continue_statement(void);


// string.c
// 字符串管理
char *cl_create_identifier(char *str);
void cl_open_string_literal(void);
void cl_open_add_string_literal(int letter);
void cl_reset_string_literal_buffer(void);
char *cl_close_string_literal(void);

// execute.c
StatementResult cl_execute_statement_list(CL_Interpreter *inter,
										  LocalEnvironment *env,StatementList *list);
// eval.c
CL_Value cl_eval_binary_expression(CL_Interpreter *inter,LocalEnvironment *env,ExpressionType operator,
								   Expression *left,Expression *right);
CL_Value cl_eval_minus_expression(CL_Interpreter *inter,LocalEnvironment *env, Expression *operand);
CL_Value cl_eval_expression(CL_Interpreter *inter,LocalEnvironment *env, expression_s *expr);

// string_pool.c
CL_String *cl_literal_to_cl_string(CL_Interpreter *inter,char *str);
void cl_refer_string(CL_String *str);
void cl_release_string(CL_String *str);
CL_String *cl_search_cl_string(CL_Interpreter *inter,char *str);
CL_String *cl_create_colang_string(CL_Interpreter *inter,char *str);

// util.c
CL_Interpreter *cl_get_current_interpreter(void);
void cl_set_current_interpreter(CL_Interpreter *inter);
void *cl_malloc(size_t size);
void *cl_execute_malloc(CL_Interpreter *inter,size_t size);
Variable *cl_search_local_variable(LocalEnvironment *env,char *identifier);
void cl_add_local_varialbe(LocalEnvironment *env,char *identifier,CL_Value *value);
CL_NativeFunctionProc *cl_search_native_function(CL_Interpreter *inter,char *name);
FunctionDefinition *cl_search_function(char *name);
char *cl_get_operator_string(ExpressionType type);

// error.c
void cl_compile_error(CompileError id, ...);
void cl_runtime_error(int line_number, RuntimeError id, ...);

// native.c
CL_Value cl_nv_print_proc(CL_Interpreter *interpreter,int arg_count,CL_Value *args);
CL_Value cl_nv_fopen_proc(CL_Interpreter *interpreter,int arg_count,CL_Value *args);
CL_Value cl_nv_fclose_proc(CL_Interpreter *interpreter,int arg_count,CL_Value *args);
CL_Value cl_nv_fgets_proc(CL_Interpreter *interpreter,int arg_count,CL_Value *args);
CL_Value cl_nv_fputs_proc(CL_Interpreter *interpreter,int arg_count,CL_Value *args);
void cl_add_std_fp(CL_Interpreter *inter);