PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')

OPT=-Wall -Wextra -Werror -fmax-errors=1 -fno-rtti -ggdb
LIB=-L${PREFIX}/lib -lhieroparser -lcontainer -llogger
INC=-I${PREFIX}/include

default: all

all: events_test char_count_test header_test glyph_test contents_test

events_test:
	g++ ${OPT} ${INC} events_test.cpp ${LIB} -o events_test

char_count_test:
	g++ ${OPT} ${INC} char_count_test.cpp ${LIB} -o char_count_test

header_test:
	g++ ${OPT} ${INC} header_test.cpp ${LIB} -o header_test

glyph_test:
	g++ ${OPT} ${INC} glyph_test.cpp ${LIB} -o glyph_test

contents_test:
	g++ ${OPT} ${INC} contents_test.cpp ${LIB} -o contents_test
