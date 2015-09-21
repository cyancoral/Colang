#include "MEM.h"
#include "debug.h"
#define GLOBAL_VARIABLE_DEFINE
#include "crowbar.h"

static void add_native_functions(CL_Interpreter *inter)
{
    CL_add_native_function(inter, "print", cl_nv_print_proc);
    CL_add_native_function(inter, "fopen", cl_nv_fopen_proc);
    CL_add_native_function(inter, "fclose", cl_nv_fclose_proc);
    CL_add_native_function(inter, "fgets", cl_nv_fgets_proc);
    CL_add_native_function(inter, "fputs", cl_nv_fputs_proc);
}

CL_Interpreter *CL_create_interpreter(void)
{
    MEM_Storage storage;
    CL_Interpreter *interpreter;

    storage = MEM_open_storage(0);
    interpreter = MEM_storage_malloc(storage,
                                     sizeof(struct CL_Interpreter_tag));
    interpreter->interpreter_storage = storage;
    interpreter->execute_storage = NULL;
    interpreter->variable = NULL;
    interpreter->function_list = NULL;
    interpreter->statement_list = NULL;
    interpreter->current_line_number = 1;

    cl_set_current_interpreter(interpreter);
    add_native_functions(interpreter);

    return interpreter;
}

void CL_compile(CL_Interpreter *interpreter, FILE *fp)
{
    extern int yyparse(void);
    extern FILE *yyin;

    cl_set_current_interpreter(interpreter);

    yyin = fp;
    if (yyparse()) {
        /* BUGBUG */
        fprintf(stderr, "Error ! Error ! Error !\n");
        exit(1);
    }
    cl_reset_string_literal_buffer();
}

void CL_interpret(CL_Interpreter *interpreter)
{
    interpreter->execute_storage = MEM_open_storage(0);
    cl_add_std_fp(interpreter);
    cl_execute_statement_list(interpreter, NULL, interpreter->statement_list);
}

static void release_global_strings(CL_Interpreter *interpreter) {
    while (interpreter->variable) {
        Variable *temp = interpreter->variable;
        interpreter->variable = temp->next;
        if (temp->value.type == CL_STRING_VALUE) {
            cl_release_string(temp->value.u.string_value);
        }
    }
}

void CL_dispose_interpreter(CL_Interpreter *interpreter)
{
    release_global_strings(interpreter);

    if (interpreter->execute_storage) {
        MEM_dispose_storage(interpreter->execute_storage);
    }

    MEM_dispose_storage(interpreter->interpreter_storage);
}

void CL_add_native_function(CL_Interpreter *interpreter,
                        char *name, CL_NativeFunctionProc *proc)
{
    FunctionDefinition *fd;

    fd = cl_malloc(sizeof(FunctionDefinition));
    fd->name = name;
    fd->type = NATIVE_FUNCTION_DEFINITION;
    fd->u.native_f.proc = proc;
    fd->next = interpreter->function_list;

    interpreter->function_list = fd;
}
