TARGET = colang
CC=gcc
OBJS = \
  lex.yy.o\
  y.tab.o\
  main.o\
  interface.o\
  create.o\
  execute.o\
  eval.o\
  string.o\
  string_pool.o\
  util.o\
  native.o\
  error.o\
  error_message.o\
  ./memory/mem.o\
  ./debug/dbg.o
CFLAGS = -c -g -Wall -Wswitch-enum -ansi -pedantic -DDEBUG
INCLUDES = \

$(TARGET):$(OBJS)
	cd ./memory; $(MAKE);
	cd ./debug; $(MAKE);
	$(CC) $(OBJS) -o $@ -lm
clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h *~
y.tab.h : colang.y
	bison --yacc -dv colang.y
y.tab.c : colang.y
	bison --yacc -dv colang.y
lex.yy.c : colang.l colang.y y.tab.h
	flex colang.l
y.tab.o: y.tab.c colang.h MEM.h
	$(CC) -c -g $*.c $(INCLUDES)
lex.yy.o: lex.yy.c colang.h MEM.h
	$(CC) -c -g $*.c $(INCLUDES)
.c.o:
	$(CC) $(CFLAGS) $*.c $(INCLUDES)
./memory/mem.o:
	cd ./memory; $(MAKE);
./debug/dbg.o:
	cd ./debug; $(MAKE);
############################################################
create.o: create.c MEM.h debug.h colang.h CL.h CL_dev.h
error.o: error.c MEM.h colang.h CL.h CL_dev.h
error_message.o: error_message.c colang.h MEM.h CL.h CL_dev.h
eval.o: eval.c MEM.h debug.h colang.h CL.h CL_dev.h
execute.o: execute.c MEM.h debug.h colang.h CL.h CL_dev.h
interface.o: interface.c MEM.h debug.h colang.h CL.h CL_dev.h
main.o: main.c CL.h MEM.h
native.o: native.c MEM.h debug.h colang.h CL.h CL_dev.h
string.o: string.c MEM.h colang.h CL.h CL_dev.h
string_pool.o: string_pool.c MEM.h debug.h colang.h CL.h CL_dev.h
util.o: util.c MEM.h debug.h colang.h CL.h CL_dev.h
