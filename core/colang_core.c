#include <stdio.h>

typedef struct CL_Interpreter_tag CL_Interpreter;

CL_Interpreter *CL_create_interpreter(void);
void CL_compile(CL_Interpreter *interpreter, FILE *fp);
void CL_interpret(CL_Interpreter *interpreter);
void CL_dispose_interpreter(CL_Interpreter *interpreter);

