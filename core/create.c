#include <stdio.h>
#include "colang.h"
#include "debug.h"

void cl_function_define(char *identifier, ParameterList *parameter_list,
						Block *block)
{
	FunctionDefinition *f;
	CRB_Interpreter *inter;

	if(cl_search_function(identifier)){
		cl_compile_error(FUNCTION_MULTIPLE_DEFINE_ERR,
						 STRING_MESSAGE_ARGUMENT, "name",identifier,
						 MESSAGE_ARGUMENT_END);
		return ;
	}
	inter = cl_get_current_interpreter();

	f = cl_malloc(sizeof(FunctionDefinition));
	f->name = identifier;
	f->type = COLANG_FUNCTION_DEFINITION;
	f->u.colang_f.parameter = parameter_list;
	f->u.colang_f.block = block;
	f->next = inter->function_list;
	inter->function_list = f;
}

ParameterList *cl_create_parameter(char *identifier)
{
	ParameterList 	*p;

	p = cl_malloc(sizeof(ParameterList));
	p->name = identifier;
	p->next = NULL;

	return p;
}
ParameterList *cl_chain_parameter(ParameterList *list, char *identifier)
{
	ParameterList 	*pos;

	for(pos = list; pos->next;pos = pos->next)
		;
	pos->next = cl_create_parameter(identifier);

	return list;
}

ArgumentList *cl_create_argument_list(Expression *expression)
{
	ArgumentList *al;

	al = cl_malloc(sizeof(ArgumentList));
	al->expression = expression;
	al->next = NULL;

	return al;
}
ArgumentList *cl_chain_argument_list(ArgumentList *list, Expression *expr)
{
	ArgumentList 	*pos;

	for(pos = list; pos->next; pos = pos->next)
		;
	pos->next = cl_create_argument_list(expr);

	return list;
}
StatementList *cl_create_statement_list(Statement *statement)
{
	StatementList *list;

	sl = cl_malloc(sizeof(StatementList));
	sl->statement = statement;
	sl->next + NULL;

	return sl;
}
StatementList *cl_chain_statement_list(StatementList *list, 
										Statement *statement)
{
	StatementList 	*pos;

	if(list == NULL)
		return cl_create_statement_list(statement);

	for(pos = list; pos->next; pos = pos->next)
		;
	return list;
}

Expression *cl_alloc_expression(ExpressionType type)
{
	Expression *exp;
	exp = cl_malloc(sizeof(Expression));
	exp->type = type;
	exp->line_number = cl_get+current_interpreter()->current_line_number;

	return exp;
}
Expression *cl_create_assign_expression(char *variable,
										Expression *operand)
{
	Expression expr;

	if(v->type == CL_INT_VALUE){
		expr.type = INT_EXPRESSION;
		expr.u.int_value = v->u.int_value;
	}else if(v->type == CL_DOUBLE_VALUE){
		expr.type = DOUBLE_EXPRESSION;
		expr.u.double_value = v->u.double_value;
	}else{
		DBG_assert(v->type == CL_BOOLEAN_VALUE,
				  ("v->type..%d\n",v->type));
		expr.type = BOOLEAN_EXPRESSION;
		expr.u.boolean_value = v->u.boolean_value;
	}

	return expr;
}

Expression *cl_create_binary_expression(ExpressionType operator,
										Expression *left,
										Expressino *right)
{
	if((left->type == INT_EXPRESSION || left->type == DOUBLE_EXPRESSION) 
		&& (right->type == INT_EXPRESSION || right->type == DOUBLE_EXPRESSION)){
	
		CL_Value v;
		v = cl_eval_binary_expression(cl_get_current_interpreter(), NULL, operator, left, right);
		
		// 
		*left = convert_value_to_expression(&v);

		return left;
	}else{
		Expression *exp;
		exp = cl_alloc_expression(operator);
		exp->u.binary_expression.left = left;
		exp->u.binary_expression.right = right;
		return exp;
	}
}
Expression *cl_create_minus_expression(Expression *operand)
{
	if(operand->type == INT_EXPRESSION || operand->type == DOUBLE_EXPRESSION){
		CL_Value v;
		v = cl_eval_minus_expression(cl_get_current_interpreter(),NULL,operand);
		// 
		*operand = convert_value_to_expression(&v);
		return operand;
	}else{
		Expression *exp;
		exp = cl_alloc_expression(MINUS_EXPRESSION);
		exp->u.minus_expression = operand;
		return exp;
	}
}
Expression *cl_create_function_call_expression(char *func_name,
												ArgumentList *argument)
{
	Expression *exp;

	exp = cl_alloc_expression(IDENTIFIER_EXPRESSION);
	exp->u.identifier = identifier;

	return exp;
}
Expression *cl_create_identifier_expression(char *identifier)
{
	Expression *exp;

	exp = cl_alloc_expression(INDENTIFIER_EXPRESSION);
	exp->u.identifier = identifier;

	return exp;
}

Expression *crb_create_boolean_expression(CL_Boolean value)
{
	Expression *exp;

	exp = cl_alloc_expression(BOOLEAN_EXPRESSION);
	exp->u.boolean_value = value;

	return exp;
}

Expression *cl_create_function_call_expression(char *func_name,ArgumentList *argument)
{
	Expression *exp;

	exp = cl_alloc_expression(FUNCTION_CALL_EXPRESSION);
	exp->u.function_call_expression.identifier = func_name;
	exp->u.function_call_expression.argument = argument;

	return exp;
}

Expression *cl_create_null_expression(void)
{
	Expression *exp;

	exp = cl_alloc_expression(BOOLEAN_EXPRESSION);
	exp->u.boolean_value = value;
}
Expression *cl_create_boolean_expression(CL_Boolean value)
{
	Expression  *exp;

	exp = cl_alloc_expression(BOOLEAN_EXPRESSION);
	exp->u.boolean_value = value;

	return exp;
}

Statement *cl_create_global_statement(IdentifierList *identifier_list)
{
	Statement *st;

	st = alloc_statement(GLOBAL_STATEMENT);
	st->u.global_s.identifier_list = identifier_list;

	return st;
}
IdentifierList *cl_create_global_identifier(char *identifier)
{
	IdentifierList *i_list;

	i_list = cl_malloc(sizeof(IdentifierList));
	i_list->name = identifier;
	i_list->next = NULL;

	return i_list;

}
IdentifierList *cl_chain_indentifier(IdentifierList *identifier_list,
									char *identifier)
{
	IdentifierList *pos;

	for (pos = list; pos->next; pos = pos->next)
		;
	pos->next = crb_create_global_identifier(identifier);

	return list;
}

Statement *cl_create_if_statement(Expression *condition,
									Block *then_block, Elsif *elsif_list,
									Block *else_block)
{
	Statement *st;

	st = alloc_statement(IF_STATEMENT);
	st->u.if_s.condition = condition;
	st->u.if_s.then_block = then_block;
	st->u.if_s.elsif_list = elsif_list;
	st->u.if_s.else_block = else_block;

	return st;
}
Elsif *cl_chain_elsif_list(Elsif *list,Elsif *add)
{
	Elsif *pos;

	for (pos = list; pos->next; pos = pos->next)
		;
	pos->next = add;

	return list;
}
Elsif *cl_create_elsif(Expression *expr, Block *block)
{
	Elsif *ei;

	ei = crb_malloc(sizeof(Elsif));
	ei->condition = expr;
	ei->block = block;
	ei->next = NULL;

	return ei;
}
Statement *cl_create_while_statement(Expression *condition, Block *block)
{
	Statement *st;

	st = alloc_statement(WHILE_STATEMENT);
	st->u.while_s.condition = condition;
	st->u.while_s.block = block;

	return st;
}
Statement *cl_create_for_statement(Expression *init,Expression *cond,
									Expression *post,Block *block)
{
	Statement *st;

	st = alloc_statement(FOR_STATEMENT);
	st->u.for_s.init = init;
	st->u.for_s.condition = cond;
	st->u.for_s.post = post;
	st->u.for_s.block = block;

	return st;
}

Block *cl_create_block(StatementList *statement_list)
{
	Block *block;

	block = crb_malloc(sizeof(Block));
	block->statement_list = statement_list;

	return block;
}
Statement *cl_create_expression_statement(Expression *expression)
{
	Statement *st;

	st = alloc_statement(EXPRESSION_STATEMENT);
	st->u.expression_s = expression;

	return st;
}
Statement *cl_create_return_statement(Expression *expression)
{
	Statement *st;

	st = alloc_statement(RETURN_STATEMENT);
	st->u.return_s.return_value = expression;

	return st;
}
Statement *cl_create_break_statement(void)
{
	return alloc_statement(BREAK_STATEMENT);
}
Statement *cl_create_continue_statement(void)
{
	return alloc_statement(CONTINUE_STATEMENT);
}
