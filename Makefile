CXX = g++
EXEC = a4q1
CXXFLAGS = -std=c++14 -Wall -MMD -g -Werror=vla
OBJECTS = board.o main.o pieces.o subject.o observer.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
