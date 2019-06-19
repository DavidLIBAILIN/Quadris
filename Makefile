XX=g++
CXXFLAGS=-std=c++14 -Wextra -Wpedantic -Wall -Werror=vla -MMD -g
OBJECTS=main.o cell.o grid.o window.o textdisplay.o graphics.o block.o level.o level0.o level1.o level2.o level3.o level4.o lBlock.o oBlock.o tBlock.o iBlock.o sBlock.o zBlock.o jBlock.o

DEPENDS=${OBJECTS:.o=.d}
	EXEC=quadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
.PHONY: clean
