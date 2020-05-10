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


void receive_response(int &sockfd, set < tuple < string, int, int > > &IPs,
    vector < int > &times);

void delete_bad_packages( set < tuple < string, int, int > > &IPs,
	vector < pair < int, int > > sent_ids, set < string > &valid_IPs);

void show_response(int ttl, set < string > valid_IPss,
    vector < int > times, bool &reached, string ip);



#endif
