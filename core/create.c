#include <stdio.h>
#include "colang.h"

void cl_function_define(char *identifier, ParameterList *parameter_list,
						Block *block)
{

}

ParameterList *cl_create_parameter(char *identifier)
{

}
ParameterList *cl_chain_parameter(ParameterList *list, char *identifier)
{

}

ArgumentList *cl_create_argument_list(Expression *expression)
{

}
ArgumentList *cl_chain_argument_list(ArgumentList *list, Expression *expr)
{

}
StatementList *cl_create_statement_list(Statement *statement)
{

}
StatementList *cl_chain_statement_list(StatementList *list, 
										Statement *statement)
{

}

Expression *cl_alloc_expression(ExpressionType type)
{

}
Expression *cl_create_assign_expression(char *variable,
										Expression *operand)
{

}

Expression *cl_create_binary_expression(ExpressionType operator,
										Expression *left,
										Expressino *right)
{

}
Expression *cl_create_minus_expression(Expression *operand)
{

}
Expression *cl_create_function_call_expression(char *func_name,
												ArgumentList *argument)
{

}
Expression *cl_create_identifier_expression(char *identifier)
{

}
Expression *cl_create_null_expression(void)
{

}
Expression *cl_create_boolean_expression(CL_Boolean value)
{

}

Statement *cl_create_global_statement(IdentifierList *identifier_list)
{

}
IdentifierList *cl_create_global_identifier(char *identifier)
{

}
IdentifierList *cl_chain_indentifier(IdentifierList *identifier_list,
									char *identifier)
{

}

Statement *cl_create_if_statement(Expression *condition,
									Block *then_block, Elsif *elsif_list,
									Block *else_block)
{

}
Elsif *cl_chain_elsif_list(Elsif *list,Elsif *add)
{

}
Elsif *cl_create_elsif(Expression *expr, Block *block)
{

}
Statement *cl_create_while_statement(Expression *condition, Block *block)
{

}
Statement *cl_create_for_statement(Expression *init,Expression *cond,
									Expression *post,Block *block)
{

}

Block *cl_create_block(StatementList *statement_list)
{

}
Statement *cl_create_expression_statement(Expression *expression)
{

}
Statement *cl_create_return_statement(Expression *expression)
{

}
Statement *cl_create_break_statement(void)
{

}
Statement *cl_create_continue_statement(void)
{

}
