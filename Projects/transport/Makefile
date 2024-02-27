CC = g++
STD = -std=c++17
FLAGS = -Wall -Wextra #-static-libstdc++

all:
	@$(CC)  $(FLAGS) -c main.cpp -o main.o
	@$(CC)  $(FLAGS) -c util.cpp -o util.o
	@$(CC)  $(FLAGS) main.o util.o -o transport

clean:
	@rm -f *.o
	@echo "Removed .o files"

distclean:
	@rm -f *.o
	@rm -f transport
	@echo "Removed .o and transport file"


