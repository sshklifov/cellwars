PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')
LIBDIR=${PREFIX}/lib
INCLUDEDIR=${PREFIX}/include/Container

OPT=-Wall -Wextra -Werror -fmax-errors=1 -fno-rtti -ggdb
INC=-I${PREFIX}/include

default: install

install: dirs header lib

dirs:
	mkdir -p ${INCLUDEDIR}
	mkdir -p ${LIBDIR}

header: dirs
	cp *.h *.inl ${INCLUDEDIR}

lib:
	g++ -c ${OPT} ${INC} String.cpp -o String.o
	g++ -c ${OPT} ${INC} BoolVector.cpp -o BoolVector.o
	g++ -c ${OPT} ${INC} OutputStringStream.cpp -o OutputStringStream.o
	g++ -c ${OPT} ${INC} InputStringStream.cpp -o InputStringStream.o
	g++ -c ${OPT} ${INC} StringStreamState.cpp -o StringStreamState.o
	ar rcs ${LIBDIR}/libcontainer.a *.o
	rm *.o
