/*
Dawid
Dieu
302052
*/

#pragma once
#ifndef icmp_receive

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
using namespace std;


void receive_response(int &sockfd, sockaddr_in &dest, bool &reached,
    set < string > &IPs, vector < int > &times, u_int8_t buffer[], sockaddr_in &sender, char *ip);
void show_response(int ttl, set < string > IPs, vector < int > times);



#endif
