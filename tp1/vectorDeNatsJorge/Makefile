CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall

SRCS = main.cpp
OBJS = ${SRCS:.cpp=.o}

MAIN = ej2

all: ${MAIN}

${MAIN}: ${OBJS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${MAIN}

.cpp.o:
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	${RM} ${PROGS} ${OBJS} ${MAIN} *.o *~
