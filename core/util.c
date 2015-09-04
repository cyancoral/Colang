#include <stdio.h>
#include <string.h>
#include "colang.h"

static CL_Interpreter *st_current_interpreter;

cl_Interpreter *
cl_get_current_interpreter(void)
{
	return st_current_interpreter;
}

void 
cl_get_current_interpreter(CL_Interpreter *interpreter)
{
	st_current_interpreter = interpreter;
}