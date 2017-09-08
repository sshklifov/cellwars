PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')
LIBDIR=${PREFIX}/lib
INCLUDEDIR=${PREFIX}/include/Misc

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
	g++ -c ${OPT} ${INC} LocalPtr.cpp -o LocalPtr.o
	g++ -c ${OPT} ${INC} SourceFile.cpp -o SourceFile.o
	ar rcs ${LIBDIR}/libmisc.a *.o
	rm *.o
