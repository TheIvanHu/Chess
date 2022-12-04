CXX = g++
EXEC = chess
CXXFLAGS = -std=c++14 -Wall -MMD -g -Werror=vla
OBJECTS =  pieces.o  observer.o  board.o  subject.o player.o main.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
