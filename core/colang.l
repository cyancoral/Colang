%{
#include <stdio.h>
#include "colang.h"
#include "y.tab.h"

int
yywrap(void)
{
	return 1;
}

static void
increment_line_number(void)
{
	cl_get_current_interpreter()->line_number++;
}
%}
%start COMMENT
%%
<INITIAL>"function" 	return FUNCTION;
<INITIAL>"if"			return IF;
<INITIAL>"else"			return ELSE;
<INITIAL>"elsif"		return ELSIF;
<INITIAL>"while"		return WHILE;
<INITIAL>"for"			return FOR;
<INITIAL>"return"		return RETURN;
<INITIAL>"break"		return BREAK;
<INITIAL>"continue"		return CONTINUE;
<INITIAL>"null"			return NULL_T;
<INITIAL>"true"			return TRUE_T;
<INITIAL>"false"		return FALSE_T;
<INITIAL>"global"		return GLOBAL_T;
<INITIAL>"("			return LP;
<INITIAL>")"			return RP;
<INITIAL>"{"			return LC;
<INITIAL>"}"			return RC;
<INITIAL>";"			return SEMICOLON;
<INITIAL>","			return COMMA;
<INITIAL>"&&"			return LOGICAL_AND;
<INITIAL>"||"			return LOGICAL_OR;
<INITIAL>"="			return ASSIGN;
<INITIAL>"=="			return EQ;
<INITIAL>"!="			return NE;
<INITIAL>">"			return GT;
<INITIAL>">="			return GE;
<INITIAL>"<"			return LT;
<INITIAL>"<="			return LE;
<INITIAL>"+"			return ADD;
<INITIAL>"-"			return SUB;
<INITIAL>"*"			return MUL;
<INITIAL>"/"			return DIV;
<INITIAL>"%"			return MOD;

<INITIAL>[A-Za-z_$][A-za-z_$0-9]* {
	yylval.identifier = cl_create_identifier(yytext);
	return IDENTIFIER;
}

<INITIAL>([1-9][0-9]*)|"0" {
	Expression *expression = cl_alloc_expression(INT_EXPRESSION);
	sscanf(yytext,"%d",&expression->u.int_value);
	yylval.expression = expression;
	return INT_LITERAL;
}

<INITIAL>[0-9]+\.[0-9]+ {
	Expression *expression = cl_alloc_expression(DOUBLE_EXPRESSION);
	sscanf(yytext,"%lf",&expression->u.double_value);
	yylval.expression = expression;
	return DOUBLE_LITERAL;
}

<INITIAL>[ \t] ;

<INITIAL>\n {
	increment_line_number();
}

<INITIAL># {
	
	BEGIN COMMENT;
}

<INITIAL>\/\/ {

	BEGIN COMMENT;
}
<INITIAL>. {

}
<COMMENT>\n {
	BEGIN INITIAL;
}
<COMMENT>. ;
%%