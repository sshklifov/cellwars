PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')

OPT=-Wall -Wextra -Werror -fmax-errors=1 -fno-rtti -ggdb
LIB=-L${PREFIX}/lib -llogger -lcontainer
INC=-I${PREFIX}/include

default: all

all: iterator_test reverse_iterator_test algorithm_test string_test bool_vector_test string_stream_state input_string_stream_test output_string_stream_test

iterator_test:
	g++ ${OPT} ${INC} iterator_test.cpp ${LIB} -o iterator_test

reverse_iterator_test:
	g++ ${OPT} ${INC} reverse_iterator_test.cpp ${LIB} -o reverse_iterator_test

algorithm_test:
	g++ ${OPT} ${INC} algorithm_test.cpp ${LIB} -o algorithm_test

string_test:
	g++ ${OPT} ${INC} string_test.cpp ${LIB} -o string_test

bool_vector_test:
	g++ ${OPT} ${INC} bool_vector_test.cpp ${LIB} -o bool_vector_test

string_stream_state_test:
	g++ ${OPT} ${INC} string_stream_state_test.cpp ${LIB} -o string_stream_state_test

input_string_stream_test:
	g++ ${OPT} ${INC} input_string_stream_test.cpp ${LIB} -o input_string_stream_test

output_string_stream_test:
	g++ ${OPT} ${INC} output_string_stream_test.cpp ${LIB} -o output_string_stream_test
