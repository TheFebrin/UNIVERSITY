/*
Dawid
Dieu
302052
*/

#pragma once
#ifndef icmp_send

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
using namespace std;




void print_as_bytes (unsigned char* buff, ssize_t length);
u_int16_t compute_icmp_checksum (const u_int16_t *buff, int length);
void fill_header(struct icmphdr *icmp_header, int ttl, int i);
void send_packages(int &sockfd, char *ip, int &ttl, vector < pair < int, int > > &sent_ids);


#endif
