# shell

yacc -dv mycalc.y ./src

flex mycalc.l ./src

gcc -o mycalc ./src/y.tab.c ./src/lex.yy.c

# platform

windows + gitshell + gcc

it's surprise that git-shell has `yacc` and `flex`.