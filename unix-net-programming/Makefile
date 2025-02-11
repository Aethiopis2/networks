CC = g++
INC = -Iinclude


PROGS = bin/daytimetcpcli bin/daytimetcpcli6 bin/daytimetcpserv

all: ${PROGS}

bin/daytimetcpcli: src/intro/daytimetcpcli.cpp lib/errorsh.cpp
	${CC} ${INC} -o $@ $^

bin/daytimetcpcli6: src/intro/daytimetcpcli6.cpp lib/errorsh.cpp
	${CC} ${INC} -o $@ $^

bin/daytimetcpserv: src/intro/daytimetcpserv.cpp lib/wrapsock.cpp lib/errorsh.cpp
	${CC} ${INC} -o $@ $^