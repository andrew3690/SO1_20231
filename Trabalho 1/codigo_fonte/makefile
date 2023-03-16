CC = g++
CFLAGS = -g -Wall -std=c++17
INCLUDES = cpu.cc main.cc main_class.cc
OBJ = main

check: 
	valgrind --leak-check=full --show-leak-kinds=all ./main

main:
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS}
	rm *.o