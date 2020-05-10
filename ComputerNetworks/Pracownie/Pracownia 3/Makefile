ROOT = sudo
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Wshadow -pedantic -pedantic-errors

transport: transport.o
	$(ROOT) $(CC) $(FLAGS) transport.o -o transport

transport.o: transport.cpp
	$(ROOT) $(CC) -c $(FLAGS) transport.cpp -o transport.o

# receive.o: receive.cpp
# 	$(ROOT) $(CC) -c $(FLAGS) receive.cpp -o receive.o
#
# send.o: send.cpp
# 	$(ROOT) $(CC) -c $(FLAGS) send.cpp -o send.o
#
# functions.o: functions.cpp
# 	$(ROOT) $(CC) -c $(FLAGS) functions.cpp -o functions.o

clean:
	sudo rm -f *.o

distclean:
	sudo rm -f transport
	sudo rm -f *.o

all : traceroute
