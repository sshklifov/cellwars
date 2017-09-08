PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')
LIBDIR=${PREFIX}/lib
INCLUDEDIR=${PREFIX}/include/inet

OPT=-Wall -Wextra -fno-rtti -fno-exceptions
INC=-I${PREFIX}/include

default: install

install: dirs libinet.a inet.h

dirs:
	mkdir -p ${INCLUDEDIR}
	mkdir -p ${LIBDIR}

libinet.a: inet.o dirs 
	ar rcs ${LIBDIR}/libinet.a inet.o
	rm inet.o

inet.o: dirs
	g++ -c ${OPT} ${INC} inet.c -o inet.o

inet.h: dirs
	cp inet.h ${INCLUDEDIR}

clean:
	rm *.o
