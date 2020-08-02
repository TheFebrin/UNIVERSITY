/*
Dawid
Dieu
302052
*/

#pragma once
#ifndef UDP

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <bits/stdc++.h>

#include "functions.hpp"
#include "udp_datagram.hpp"

using namespace std;


#define BUFFER_SIZE 2048

class UDP
{
private:
	int WINDOW_SIZE = 500;
	int DATAGRAM_SIZE = 1000;

	int N_BYTES_REQUESTED;       // how many bytes of file we request
	int N_DATAGRAMS_NEEDED;
	int n_datagrams_saved = 0;   // datagrams already received and saved
	int id_datagram_sent = 0;    // latest datagram sent

	char *ip_address;
	int port;
	ofstream output_file;
	struct sockaddr_in server_addr;
	int sockfd;

	/* each datagram has DATAGRAM_SIZE bytes of memory */
	unordered_map < int, Datagram > Datagrams;				 // map of Datagrams that need to be send to server
	unordered_map < int, int > request_to_datagram_id;  	 // given a particular request returns the datagram which contains it
	unordered_set < int > not_received; 

public:
	UDP();
	UDP(int window_size, int datagram_size, char* argv[]);
	~UDP();

	int init_socket();
	bool transport_completed();

	void send_requests();
	void receive_data();
	void save_data();
	void request_data();
	void close_file();
};


#endif
