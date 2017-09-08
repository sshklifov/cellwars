PREFIX=$(shell pwd | sed 's/\(cellwars\).*/\1/')
LIBDIR=${PREFIX}/lib
INCLUDEDIR=${PREFIX}/include/Container

OPT=-Wall -Wextra -Werror -fmax-errors=1 -fno-rtti -ggdb
INC=-I${PREFIX}/include $(pkg-config --cflags glfw3 glm)
LOCAL_LIB=-L${LIBDIR} -lapplication -lrenderutils -lepsilon -lhieroparser -lcontainer -lmisc -llogger -lglad
SYSTEM_LIB=$(shell pkg-config --libs glfw3 glm) -ldl

default: main

main:
	g++ ${OPT} ${INC} src/Main.cpp ${LOCAL_LIB} ${SYSTEM_LIB} -o cellwars

local_libs: glad logger misc stb epsilon container hieroparser renderutils application

glad:
	cd src/glad && make

logger:
	cd src/logger && make

misc:
	cd src/Misc && make

stb:
	cd src/stb && make

epsilon:
	cd src/Epsilon && make

container:
	cd src/Container && make

hieroparser:
	cd src/HieroParser && make

renderutils:
	cd src/RenderUtils && make

application:
	cd src/Application && make
