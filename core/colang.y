%{
#include <stdio.h>
#include "colang.h"
#define YYDEBUG 1
%}
%union{
	char 			*identifier;
	ParameterList 	*parameter_list;
	ArgumentList	*argument_list;
	Expression		*expression;
	Statement		*statement;
	StatementList 	*statement_list;
	Block			*block;
	elsif			*elsif;
	IdenifierList	*identifier_list;
}
%token 	<expression> INT_LITERAL
%token 	<expression> DOUBLE_LITERAL
%token  <expression> STRING_LITERAL
%token 	<identifier> IDENTIFIER
%token 	FUNCTION IF ELSE ELSIF WHILE FOR RETURN_T BREAK CONTINUE NULL_T
		LP RP LC RC SEMICOLON COMMA ASSIGN LOGICAL_AND LOGICAL_OR
		EQ NE GT GE LT LE ADD SUB MUL DIV MOD TRUE_T FALSE_T GLOBAL_T		
%type 	<parameter_list> parameter_list
%type 	<argument_list> argument_list
%type   <expression> expression expression_opt
        logical_and_expression logical_or_expression
        equality_expression relational_expression
        additive_expression multiplicative_expression
        unary_expression primary_expression
%type   <statement> statement global_statement
        if_statement while_statement for_statement
        return_statement break_statement continue_statement
%type   <statement_list> statement_list
%type   <block> block
%type   <elsif> elsif elsif_list
%type   <identifier_list> identifier_list
%%
translation_unit
	: definition_or_statement
	| translation_unit definition_or_statement
	;
definition_or_statement
	: function_definition
	| statement
	{
		// 声明

	}
	;
function_definition
	: FUNCTION IDENTIFIER LP parameter_list RP block
	{
		// 有参数函数定义

	}
	| FUNCTION IDENTIFIER LP RP block
	{
		// 无参数函数定义

	}
	;
parameter_list
	: IDENTIFIER
	{
		// 单个参数

	}
	| parameter_list COMMA IDENTIFIER
	{
		// 多个参数

	}
	;
argument_list
	: expression
	{

	}
	| argument_list COMMA expression
	{

	}
	;
statement_list
	: statement
	{

	}
	| statement_list statement
	{

	}
	;
expression
	: logical_or_expression
	| IDENTIFIER ASSIGN expression
	{

	}
	;
logical_or_expression
	: logical_and_expression
	| logical_or_expression LOGICAL_OR logical_and_expression
	{

	}
	;
logical_and_expression
	: equality_expression
	| logical_and_expression LOGICAL_AND equality_expression
	{

	}
	;
equality_expression
	: relational_expression
	| equality_expression EQ relational_expression
	{

	}
	| equality_expression NE relational_expression
	{

	}
	;
relational_expression
	: additive_expression
	| relational_expression GT additive_expression
	{

	}
	| relational_expression GE additive_expression
	{

	}
	| relational_expression LE additive_expression{

	}
	;
additive_expression
	: multiplicative_expression
	| additive_expression ADD multiplicative_expression
	{

	}
	| additive_expression SUB multiplicative_expression
	{

	}
	;
multiplicative_expression
	: unary_expression
	| multiplicative_expression MUL unary_expression
	{

	}
	| multiplicative_expression DIV unary_expression
	{

	}
	| multiplicative_expression MOD unary_expression
	{

	}
	;
unary_expression
	: primary_expression
	| SUB unary_expression
	{

	}
	;
primary_expression
	: IDENTIFIER LP argument_list RP
	{

	}
	| IDENTIFIER LP RP
	{

	}
	| LP expression RP
	{

	}
	| IDENTIFIER
	{

	}
	| INT_LITERAL
	| DOUBLE_LITERAL
	| TRUE_T
	{

	}
	| FALSE_T
	{

	}
	| NULL_T
	{

	}
	;
statement
	: expression SEMICOLON // 分号
	{

	}
	| global_statement
	| if_statement
	| while_statement
	| for_statement
	| return_statement
	| break_statement
	| continue_statement
	;
global_statement
	: GLOBAL_T identifier_list SEMICOLON
	{

	}
	;
identifier_list
	: IDENTIFIER
	{

	}
	| identifier_list COMMA IDENTIFIER
	{

	}
	;
if_statement
	: IF LP expression RP block
	{

	}
	| IF LP expression RP block
	{

	} 
	| IF LP expression RP block elsif_list
	{

	}
	| IF LP expression RP block elsif_list ELSE block
	{

	}
	;
elsif_list
	: elsif_list elsif
	{

	}
	;
elsif
	: ELSIF LP expression RP block
	{

	}
	;
while_statement
	: WHILE LP expression RP block
	{

	}
	;
for_statement
	: FOR LP expression_opt SEMICOLON expression_opt SEMICOLON expression_opt RP block
	{

	}
	;
expression_opt
	: // empty
	{

	}
	| expression
	;
return_statement
	: RETURN_T expression_opt SEMICOLON
	{

	}
	;
break_statement
	: BREAK SEMICOLON
	{

	}
	;
continue_statement
	: CONTINUE SEMICOLON
	{

	}
	;
block
	: LC statement_list RC 
	{

	}
	| LC RC
	{

	}
	;
%%
int
yyerror(char const *str)
{
	extern char *yytext;
	fprintf(stderr,"parser error near %s\n", yytext);
}

int main(void)
{
	extern int yyparse(void);
	extern FILE *yyin;

	yyin = stdin;
	if(yyparse()){
		fprintf(stderr,"Error!\n");
		exit(1);
	}	
}