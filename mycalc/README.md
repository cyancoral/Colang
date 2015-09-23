# shell

yacc -dv mycalc.y

flex mycalc.l

gcc -o mycalc y.tab.c lex.yy.c

# platform

*windows

download gitshell + gcc

git-shell has `yacc` and `flex`.

*linux

use the same commands.