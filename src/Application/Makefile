PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')
LIBDIR=${PREFIX}/lib
INCLUDEDIR=${PREFIX}/include/Application

OPT=-Wall -Wextra -Werror -fmax-errors=1 -ggdb
INC=-I${PREFIX}/include

default: install

install: dirs header lib

dirs:
	mkdir -p ${INCLUDEDIR}
	mkdir -p ${LIBDIR}

header: dirs
	cp *.h *.inl ${INCLUDEDIR}

lib:
	g++ -c ${OPT} ${INC} CalibriFont.cpp -o CalibriFont.o
	g++ -c ${OPT} ${INC} Application.cpp -o Application.o
	g++ -c ${OPT} ${INC} Arena.cpp -o Arena.o
	g++ -c ${OPT} ${INC} StageLogin.cpp -o StageLogin.o
	g++ -c ${OPT} ${INC} StageMain.cpp -o StageMain.o
	g++ -c ${OPT} ${INC} RenderCircle.cpp -o RenderCircle.o
	g++ -c ${OPT} ${INC} RenderBlob.cpp -o RenderBlob.o
	g++ -c ${OPT} ${INC} RenderLines.cpp -o RenderLines.o
	g++ -c ${OPT} ${INC} RenderGeometryContainer.cpp -o RenderGeometryContainer.o
	g++ -c ${OPT} ${INC} Bot.cpp -o Bot.o
	ar rcs ${LIBDIR}/libapplication.a *.o
	rm *.o

#TODO: remove Bot
