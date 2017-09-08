PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')

OPT=-Wall -Wextra -Werror -fmax-errors=1 -fno-rtti -ggdb
LIB=-L${PREFIX}/lib -lrenderutils -lhieroparser -lcontainer -lmisc -llogger
INC=-I${PREFIX}/include

default: atlas_test

all: local_ptr_test atlas_test

local_ptr_test:
	g++ ${OPT} ${INC} local_ptr_test.cpp ${LIB} -o local_ptr_test

atlas_test:
	g++ ${OPT} ${INC} atlas_test.cpp ${LIB} -o atlas_test

# algorithm_test:
# 	g++ ${OPT} ${INC} algorithm_test.cpp ${LIB} -o algorithm_test

# string_test:
# 	g++ ${OPT} ${INC} string_test.cpp ${LIB} -o string_test

# bool_vector_test:
# 	g++ ${OPT} ${INC} bool_vector_test.cpp ${LIB} -o bool_vector_test

# string_stream_state_test:
# 	g++ ${OPT} ${INC} string_stream_state_test.cpp ${LIB} -o string_stream_state_test

# input_string_stream_test:
# 	g++ ${OPT} ${INC} input_string_stream_test.cpp ${LIB} -o input_string_stream_test

# output_string_stream_test:
# 	g++ ${OPT} ${INC} output_string_stream_test.cpp ${LIB} -o output_string_stream_test
