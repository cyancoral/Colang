yacc -dv ../colang.y
flex ../colang.l
gcc -o colang y.tab.c lex.yy.c ../colang.h ../colang_core.h ../colang_developer.h ../create.c ../debug.c ../error.c ../error_message.c ../error_message_not_gcc.c ../eval.c ../execute.c ../interface.c ../MEM.h ../native.c ../nativeif.c ../regexp.c ../string.c ../string_pool.c ../util.c ../wchar.c 2>err_log.txt