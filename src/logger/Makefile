PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')
LIBDIR=${PREFIX}/lib
INCLUDEDIR=${PREFIX}/include/logger

OPT=-Wall -Wextra -Werror -fmax-errors=1 -fno-rtti -fno-exceptions -ggdb

default: install

install: dirs liblogger.a logger.h

dirs:
	mkdir -p ${INCLUDEDIR}
	mkdir -p ${LIBDIR}

liblogger.a: logger.o dirs 
	ar rcs ${LIBDIR}/liblogger.a logger.o
	rm logger.o

logger.o: dirs
	g++ -c ${OPT} logger.c -o logger.o

logger.h: dirs
	cp logger.h ${INCLUDEDIR}

clean:
	rm *.o
