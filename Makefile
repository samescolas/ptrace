SRCS = $(wildcard srcs/*.c$)

CC = gcc

all : tracer traceme

tracer: tracer.c
traceme: traceme.c

.PHONY : clean re

clean :
	rm -f tracer
	rm -f traceme

re : clean all
