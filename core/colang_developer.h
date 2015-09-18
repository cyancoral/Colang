#ifndef PUBLIC_COLANG_DEVELOPER_H_INCLUDED
#define PUBLIC_COLANG_DEVELOPER_H_INCLUDED
#include "colang_core.h"

typedef enum {
	CL_FALSE = 0,
	CL_TRUE = 1
} CL_Boolean;

typedef struct CL_String_tag CL_String;

typedef struct {
	char *name;
} CL_NativePointerInfo;

typedef enum {
	CL_BOOLEAN_VALUE =1,
	CL_INT_VALUE,
	CL_DOUBLE_VALUE,
	CL_NATIVE_POINTER_VALUE,
	CL_NULL_VALUE
} CL_ValueType;

typedef struct {
	CL_NativePointerInfo *info;
	void				 *pointer;
} CL_NativePointer;

typedef struct {
	CL_ValueType type;
	union {
		CL_Boolean			boolean_value;
		int					int_value;
		double				double_value;
		CL_String			*string_value;
		CL_NativePointer 	native_pointer;
	} u;
} CL_Value;

typedef CL_value CL_NativeFunctionProc(CL_Interpreter *interpreter, int arg_count, CL_Value *args);

void CL_add_native_function(CL_Interpreter *interpreter,
							char *name, CL_NativeFunctionProc *proc);
void CL_add_global_variable(CL_Interpreter *inter,
							char *identifier,CL_Value *value);