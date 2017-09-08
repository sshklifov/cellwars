PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')
LIBDIR=${PREFIX}/lib
INCLUDEDIR=${PREFIX}/include/stb

OPT=-Wall -Wextra -Werror -fmax-errors=1 -fno-rtti -ggdb
INC=-I${PREFIX}/include

default: install

install: dirs header

dirs:
	mkdir -p ${INCLUDEDIR}
	mkdir -p ${LIBDIR}

header: dirs
	cp stb_image.h ${INCLUDEDIR}
