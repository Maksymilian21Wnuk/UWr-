CC = gcc
STD = -std=c17
FLAGS = -Wall -Wextra

all:
	@$(CC) $(STD) $(FLAGS)  -c traceroute.c -o tr.o
	@$(CC) $(STD) $(FLAGS)  -c util.c -o util.o
	@$(CC) $(STD) $(FLAGS)  tr.o util.o -o traceroute

clean:
	@rm -f *.o
	@echo "Removed .o files"
distclean:
	@rm -f *.o
	@rm -f traceroute
	@echo "Removed .o and traceroute file"
