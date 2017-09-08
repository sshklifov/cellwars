PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')
LIBDIR=${PREFIX}/lib
INCLUDEDIR=${PREFIX}/include/RenderUtils

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
	g++ -c ${OPT} ${INC} Font.cpp -o Font.o
	g++ -c ${OPT} ${INC} GladInit.cpp -o GladInit.o
	g++ -c ${OPT} ${INC} GlfwInit.cpp -o GlfwInit.o
	g++ -c ${OPT} ${INC} Matrices.cpp -o Matrices.o
	g++ -c ${OPT} ${INC} Program.cpp -o Program.o
	g++ -c ${OPT} ${INC} Shader.cpp -o Shader.o
	ar rcs ${LIBDIR}/librenderutils.a *.o
	rm *.o
