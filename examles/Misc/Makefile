PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')

OPT=-Wall -Wextra -Werror -fmax-errors=1 -fno-rtti -ggdb
LIB=-L${PREFIX}/lib -lmisc -lcontainer -llogger
INC=-I${PREFIX}/include

default: source_file_test

all: local_ptr_test source_file_test

local_ptr_test:
	g++ ${OPT} ${INC} local_ptr_test.cpp ${LIB} -o local_ptr_test

source_file_test:
	g++ ${OPT} ${INC} source_file_test.cpp ${LIB} -o source_file_test

