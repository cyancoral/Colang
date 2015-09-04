yacc -dv ../colang.y
flex ../colang.l
gcc -o colang y.tab.c lex.yy.c