PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')
LIB=-L${PREFIX}/lib -llogger
INC=-I${PREFIX}/include

default: all

all: types_test utility_test math_funcs_test

types_test:
	g++ ${INC} types_test.cpp ${LIB} -o types_test

utility_test:
	g++ ${INC} utility_test.cpp ${LIB} -o utility_test

math_funcs_test:
	g++ ${INC} math_funcs_test.cpp ${LIB} -o math_funcs_test
clipbox_test:
	g++ ${INC} clipbox_test.cpp ${LIB} -o clipbox_test -ggdb
