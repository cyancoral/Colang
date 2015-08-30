# shell

yacc -dv mycalc.y

flex mycalc.l

gcc -o mycalc y.tab.c lex.yy.c

# platform

windows + gitshell + gcc

it's surprise that git-shell has `yacc` and `flex`.