PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')
LIBDIR=${PREFIX}/lib
INCLUDEDIR=${PREFIX}/include/RenderUtils

OPT=-Wall -Wextra -Werror -fno-rtti -fno-exceptions
INC=-I${PREFIX}/include

default: install

install: dirs lib headers

dirs:
	mkdir -p ${INCLUDEDIR}
	mkdir -p ${LIBDIR}

headers: dirs
	cp *.h ${INCLUDEDIR}

lib:
	# g++ -c ${INC} BoolVector.cpp -ggdb
	# g++ -c ${INC} Shader.cpp Program.cpp
	# g++ -c ${INC} Atlas.cpp
	# ar rcs ${LIBDIR}/librenderutils.a *.o
	# rm *.o
	g++ -fmax-errors=5 ${INC} StringSegment.cpp -ggdb
	#g++ -ggdb -fmax-errors=5 ${INC} DELETE.cpp
