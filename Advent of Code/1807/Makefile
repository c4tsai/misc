CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
EXEC = advent7
OBJECTS = main.o dictionary.o scheduler.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
