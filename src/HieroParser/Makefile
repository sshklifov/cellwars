PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')
LIBDIR=${PREFIX}/lib
INCLUDEDIR=${PREFIX}/include/HieroParser

OPT=-Wall -Wextra -Wimplicit-fallthrough=2 -Werror -fmax-errors=1 -fno-rtti -ggdb
INC=-I${PREFIX}/include

default: install

install: dirs header lib

dirs:
	mkdir -p ${INCLUDEDIR}
	mkdir -p ${LIBDIR}

header: dirs
	cp *.h *.inl ${INCLUDEDIR}

lib:
	g++ -c ${OPT} ${INC} HieroEvents.cpp -o HieroEvents.o
	g++ -c ${OPT} ${INC} HieroParser.cpp -o HieroParser.o
	ar rcs ${LIBDIR}/libhieroparser.a *.o
	rm *.o
