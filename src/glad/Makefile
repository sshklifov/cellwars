PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')
LIBDIR=${PREFIX}/lib
INCLUDEDIR=${PREFIX}/include/glad

OPT=-fno-rtti -fno-exceptions -ggdb

default: install

install: dirs libglad.a glad.h

dirs:
	mkdir -p ${INCLUDEDIR}
	mkdir -p ${LIBDIR}

libglad.a: glad.o dirs 
	ar rcs ${LIBDIR}/libglad.a glad.o
	rm glad.o

glad.o: dirs
	g++ -c ${OPT} glad.c -o glad.o

glad.h: dirs
	cp glad.h ${INCLUDEDIR}

clean:
	rm *.o
