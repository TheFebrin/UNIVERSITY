/*
Dawid
Dieu
302052
*/

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>

#include "icmp_send.hpp"
#include "icmp_receive.hpp"
#include "functions.hpp"
using namespace std;

/* STRUCTS */
struct icmp header;
struct sockaddr_in sender;
struct sockaddr_in dest;

/* VARIABLES */
const int max_ttl = 30;
int ttl = 1;

int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
u_int8_t buffer[IP_MAXPACKET];
char *ip; // ip that we send packages to

/* CONNECT FUNCTION */
void connect();
bool check_if_good_ip();


int main(int argc, char* argv[])
{

    if (sockfd < 0)
    {
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }
  	else if (argc == 1)
  	{
        cout << "Given no argument!" << endl;
        cout << "Format should be:" << endl;
        cout << "$ sudo ./traceroute <IP_ADDRES>" << endl;
        return 0;
    }
  	else if (argc == 2)
    {
        ip = argv[1];
        cout << "traceroute to: "  << ip << ", " << max_ttl << " hops max" << endl;
        if(!check_if_good_ip(ip))
        {
            cout << "Wrong IP address!" << endl;
            return 0;
        }
        connect();
    }
    else
    {
        cout << "Extra arg!" << endl;
        cout << "Format should be:" << endl;
        cout << "$ sudo ./traceroute <IP_ADDRES>" << endl;
        return 0;
    }


	return EXIT_SUCCESS;
}

/* CONNECT FUNCTION */

void connect()
{
    bool reached = false;
    while (!reached and ttl <= max_ttl)
    {
        set < string > IPs;
        vector < int > times;
        send_packages(sockfd, ip, dest, ttl, header);
        receive_response(sockfd, dest, reached, IPs, times, buffer, sender, ip);
        show_response(ttl, IPs, times);

        ttl++;
    }
}
