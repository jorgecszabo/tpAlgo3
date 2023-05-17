CXX = g++
CXXFLAGS = -std=c++11 -O0 -Wall -pedantic -g

SRCS = main.cpp
OBJS = ${SRCS:.cpp=.o}

MAIN = main

all: ${MAIN}

${MAIN}: ${OBJS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${MAIN}

.cpp.o:
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	${RM} ${PROGS} ${OBJS} ${MAIN} *.o *~
	${RM} .gdb_history
