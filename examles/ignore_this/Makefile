PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')

OPT=-Wall -Wextra -Werror -fmax-errors=1 -fno-rtti -ggdb
LIB=-L${PREFIX}/lib -llogger -lcontainer
INC=-I${PREFIX}/include

default: all

all: compile_test

compile_test:
	g++ ${OPT} ${INC} compile_test.cpp ${LIB} -o compile_test
