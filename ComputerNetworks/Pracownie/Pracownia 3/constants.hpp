/*
Dawid
Dieu
302052
*/

#pragma once
#ifndef constants

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <bits/stdc++.h>

using namespace std;
using namespace chrono;

const unsigned int WINDOW_SIZE = 500;
const unsigned int BUFFER_SIZE = 2048;
const unsigned int TIMEOUT_USEC = 100000;
const unsigned int TIMEOUT_SEC = 0;
const int BATCH_SIZE = 1000;


int N_BATCHES = 0;
int N_BYTES_REQUESTED = 0;
ofstream output_file;
char *ip_address;
int port;

int last_byte_requested = 0;
int batch_index = 0;
int remaining_batches;


vector < string > send_message;
vector < string > batch_contents;
vector < time_point < system_clock > > message_send_time;
vector < bool > received_datagram;
vector < bool > batch_saved_to_file;

#endif
