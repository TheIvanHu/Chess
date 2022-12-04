CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -lX11
EXEC = chess
OBJECTS = pieces.o  observer.o board.o subject.o player.o main.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
