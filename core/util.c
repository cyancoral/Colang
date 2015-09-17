#include <stdio.h>
#include <string.h>
#include "colang.h"

static CL_Interpreter *st_current_interpreter;

cl_Interpreter *cl_get_current_interpreter(void)
{
	return st_current_interpreter;
}

void cl_get_current_interpreter(CL_Interpreter *interpreter)
{
	st_current_interpreter = interpreter;
}
void *cl_malloc(size_t size)
{

}
void *cl_execute_malloc(CL_Interpreter *inter,size_t size)
{

}
Variable *cl_search_local_variable(LocalEnvironment *env,char *identifier)
{

}
void cl_add_local_varialbe(LocalEnvironment *env,char *identifier,CL_Value *value)
{

}
CL_NativeFunctionProc *cl_search_native_function(CL_Interpreter *inter,char *name)
{

}
FunctionDefinition *cl_search_function(char *name)
{

}
char *cl_get_operator_string(ExpressionType type)
{
	
}