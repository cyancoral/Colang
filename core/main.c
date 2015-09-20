#include <stdio.h>
#include "colang_core.h"
#include "MEM.h"

int main(int argc, char **argv)
{
	CL_Interpreter		*interpreter;
	FILE 	*fp;

	if(argc != 2)
	{
		fprintf(stderr,"usage:%s filename", argv[0]);
		exit(1);
	}

	fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		fprintf(stderr, "%s not found.\n", argv[1]);
		exit(1);
	}

	interpreter = CL_create_interpreter();
	CL_compile(interpreter,fp);
	CL_interpret(interpreter);
	CL_dispose_interpreter(interpreter);

	MEM_dump_blocks(stdout);

	return 0;
}