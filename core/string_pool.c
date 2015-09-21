#include <stdio.h>
#include <string.h>
#include "MEM.h"
#include "debug.h"
#include "colang.h"

static CL_String *
alloc_cl_string(CL_Interpreter *inter, char *str, CL_Boolean is_literal)
{
    CL_String *ret;

    ret = MEM_malloc(sizeof(CL_String));
    ret->ref_count = 0;
    ret->is_literal = is_literal;
    ret->string = str;

    return ret;
}

CL_String *
cl_literal_to_cl_string(CL_Interpreter *inter, char *str)
{
    CL_String *ret;

    ret = alloc_cl_string(inter, str, CL_TRUE);
    ret->ref_count = 1;

    return ret;
}

void
cl_refer_string(CL_String *str)
{
    str->ref_count++;
}

void
cl_release_string(CL_String *str)
{
    str->ref_count--;

    DBG_assert(str->ref_count >= 0, ("str->ref_count..%d\n",
                                     str->ref_count));
    if (str->ref_count == 0) {
        if (!str->is_literal) {
            MEM_free(str->string);
        }
        MEM_free(str);
    }
}

CL_String *
cl_create_crowbar_string(CL_Interpreter *inter, char *str)
{
    CL_String *ret = alloc_cl_string(inter, str, CL_FALSE);
    ret->ref_count = 1;

    return ret;
}
