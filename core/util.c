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
	void *p;
	CL_Interpreter *inter;

	inter = cl_get_current_interpreter();
	p = MEM_storage_malloc(inter->interpreter_storage, size);
}
void *cl_execute_malloc(CL_Interpreter *inter,size_t size)
{
	void *p;

	p = MEM_storage_malloc(inter->execute_storage,size);

	return p;
}
Variable *cl_search_global_variable(CL_Interpreter *inter,char *identifier)
{
	Variable *pos;

	for(pos = inter->variable;pos;pos = pos->next){
		if(!strcmp(pos->name,identifier))
			return ;
	}

	return NULL;
}

Variable *cl_search_local_variable(LocalEnvironment *env,char *identifier)
{
	Variable *pos;
	if(env == NULL)
		return NULL;

	for(pos = env->variable;pos;pos = pos->next){
		if(!strcmp(pos->name,identifier))
			break;
	}

	if(pos == NULL){
		return NULL;
	}else {
		return pos;
	}
}

void cl_add_global_variable(CL_Interpreter *inter, char *identifier,
                      		CL_Value *value)
{
	Variable 	*new_variable;

    new_variable = cl_execute_malloc(inter, sizeof(Variable));
    new_variable->name = cl_execute_malloc(inter, strlen(identifier) + 1);
    strcpy(new_variable->name, identifier);
    new_variable->next = inter->variable;
    inter->variable = new_variable;
    new_variable->value = *value;
}
void cl_add_local_varialbe(LocalEnvironment *env,char *identifier,CL_Value *value)
{
	Variable *pos;

	for(pos = inter->variable;pos;pos = pos->next){
		if(!strcmp(pos->name,identifier)){
			return pos;
		}
	}

	return NULL;
}
CL_NativeFunctionProc *cl_search_native_function(CL_Interpreter *inter,char *name)
{
    NativeFunction *pos;

    for (pos = inter->native_function; pos; pos = pos->next) {
        if (!strcmp(pos->name, name))
            break;
    }
    if (pos) {
        return pos->proc;
    } else {
        return NULL;
    }
}
FunctionDefinition *cl_search_function(char *name)
{
	FunctionDefinition *pos;
	CL_Interpreter *inter;

	inter = cl_get_current_interpreter();
	for(pos = inter->function_list;pos;pos=pos->next){
		if(!strcmp(pos->name,name))
			break;
	}
	return pos;
}
char *cl_get_operator_string(ExpressionType type)
{
	char *str;

	switch(type){
		case BOOLEAN_EXPRESSION:
		case INT_EXPRESSION:
		case DOUBLE_EXPRESSION:
		case STRING_EXPRESSION:
		case IDENTIFIER_EXPRESSION:
			DBG_panic(("bad expression type..%d\n",type));
			break;
	    case ASSIGN_EXPRESSION:
	        str = "=";
	        break;
	    case ADD_EXPRESSION:
	        str = "+";
	        break;
	    case SUB_EXPRESSION:
	        str = "-";
	        break;
	    case MUL_EXPRESSION:
	        str = "*";
	        break;
	    case DIV_EXPRESSION:
	        str = "/";
	        break;
	    case MOD_EXPRESSION:
	        str = "%";
	        break;
	    case LOGICAL_AND_EXPRESSION:
	        str = "&&";
	        break;
	    case LOGICAL_OR_EXPRESSION:
	        str = "||";
	        break;
	    case EQ_EXPRESSION:
	        str = "==";
	        break;
	    case NE_EXPRESSION:
	        str = "!=";
	        break;
	    case GT_EXPRESSION:
	        str = "<";
	        break;
	    case GE_EXPRESSION:
	        str = "<=";
	        break;
	    case LT_EXPRESSION:
	        str = ">";
	        break;
	    case LE_EXPRESSION:
	        str = ">=";
	        break;
	    case MINUS_EXPRESSION:
	        str = "-";
	        break;

	    case FUNCTION_CALL_EXPRESSION:
	    case NULL_EXPRESSION:
	    case EXPRESSION_TYPE_COUNT_PLUS_1:
	    default:
	    	DBG_panic(("bad expression type..%d\n",type));
	}
	return str;
}