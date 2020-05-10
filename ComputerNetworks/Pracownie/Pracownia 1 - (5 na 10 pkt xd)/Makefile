ROOT = sudo
CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Wshadow -pedantic -pedantic-errors

traceroute: icmp_send.o icmp_receive.o traceroute.o functions.o
	$(ROOT) $(CC) $(FLAGS) icmp_send.o icmp_receive.o functions.o traceroute.o -o traceroute

traceroute.o: traceroute.cpp
	$(ROOT) $(CC) -c $(FLAGS) traceroute.cpp -o traceroute.o

icmp_send.o: icmp_send.hpp icmp_send.cpp
	$(ROOT) $(CC) -c $(FLAGS) icmp_send.cpp -o icmp_send.o

icmp_receive.o: icmp_receive.hpp icmp_receive.cpp
	$(ROOT) $(CC) -c $(FLAGS) icmp_receive.cpp -o icmp_receive.o

functions.o: functions.hpp functions.cpp
	$(ROOT) $(CC) -c $(FLAGS) functions.cpp -o functions.o


clean:
	sudo rm -f *.o

distclean:
	sudo rm -f traceroute
	sudo rm -f *.o

all : traceroute
