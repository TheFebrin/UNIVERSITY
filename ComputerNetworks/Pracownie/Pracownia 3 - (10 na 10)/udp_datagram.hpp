/*
Dawid
Dieu
302052
*/

#pragma once
#ifndef udp_datagram

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <bits/stdc++.h>

#include "functions.hpp"

using namespace std;


class Datagram
{
private:
	int port;
	double request_sent_time;
	bool sent;
	string request;  // datagram request format: GET start length
	string data;

public:
	Datagram();
	Datagram(double request_sent_time, string request, string data, int port);

	int get_port();
	double get_request_sent_time();
	string get_request();
	string get_data();
	bool get_sent();

	void set_port(int new_port);
	void set_request_sent_time(double new_time);
	void set_request(string new_request);
	void set_data(string new_data);
	void set_sent();
};


#endif
