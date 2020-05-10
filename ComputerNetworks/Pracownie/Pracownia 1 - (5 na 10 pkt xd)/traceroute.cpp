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


/* VARIABLES */
const int max_ttl = 30;
int ttl = 1;

int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
char *ip; // ip that we send packages to

/* CONNECT FUNCTION */
void connect();


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
        set < tuple < string, int, int > > IPs;
        set < string > valid_IPs;
        vector < int > times;
        vector < pair < int, int > > sent_ids;

        send_packages(sockfd, ip, ttl, sent_ids);
        receive_response(sockfd, IPs, times);
        delete_bad_packages(IPs, sent_ids, valid_IPs);
        show_response(ttl, valid_IPs, times, reached, ip);
        ttl++;
    }
}
