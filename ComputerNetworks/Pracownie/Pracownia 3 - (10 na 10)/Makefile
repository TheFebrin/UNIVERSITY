ROOT = sudo
CC = g++
FLAGS = -std=c++17 -Wall -Wextra -Wshadow

main: main.o UDP.o udp_datagram.o functions.o
	$(ROOT) $(CC) $(FLAGS) functions.o UDP.o udp_datagram.o main.o -o transport

main.o: main.cpp
	$(ROOT) $(CC) -c $(FLAGS) main.cpp -o main.o

udp_datagram.o: udp_datagram.cpp
	$(ROOT) $(CC) -c $(FLAGS) udp_datagram.cpp -o udp_datagram.o

UDP.o: UDP.cpp
	$(ROOT) $(CC) -c $(FLAGS) UDP.cpp -o UDP.o

functions.o: functions.cpp
	$(ROOT) $(CC) -c $(FLAGS) functions.cpp -o functions.o


clean:
	sudo rm -f *.o

distclean:
	sudo rm -f transport
	sudo rm -f *.o


all : main
