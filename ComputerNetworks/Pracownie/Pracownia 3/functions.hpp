/*
Dawid
Dieu
302052
*/

#pragma once
#ifndef functions

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <bits/stdc++.h>

#include "constants.hpp"

using namespace std;
using namespace chrono;


bool check_if_good_ip(char *ip)
{
    /*
    Check if every char is a digit or a dot.
    Check if every number is between [0, 255].
    Check if there are 3 dots in between the numbers.
    */
    string ip_string(ip);
    int dots = 0;

    string tmp;
    ip_string += '.';
    for(auto a: ip_string)
    {
        if(a == '.')
        {
            dots ++;
            if(tmp == "")
                return false;
            int act_num = stoi(tmp);
            if(act_num > 255)
                return false;
            tmp = "";
        }
        else if (a >= '0' and a <= '9')
            tmp += a;
        else
            return false;
    }
    return dots == 4;
}


void handle_error(string error)
{
    map < string, string > Errors = {
        {"sendto-error", "Error while sending message (sendto(...))!\n"},
        {"socket-error", "Error while opening a socket!\n"},
        {"select-error", "Error while using select!\n"},
        {"close-error", "Error while closing a file!\n"},
		{"args-error", "Given wrong arguments!\nFormat should be:\n$ ./transport <IP_ADDRESS> <PORT> <OUTPUT_FILE> <BYTES>\n"},
		{"ip-error", "Given wrong IP address!\n"},
    };

	cout << Errors[ error ] << endl;
    exit (EXIT_FAILURE);
}


int init_socket()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        handle_error("socket-error");
    }

    return sockfd;
}


void init_vectors()
{
    send_message.assign(WINDOW_SIZE, "");
    batch_contents.assign(WINDOW_SIZE, "");
    received_datagram.assign(WINDOW_SIZE, true);
    batch_saved_to_file.assign(WINDOW_SIZE, true);
    message_send_time.assign(WINDOW_SIZE, system_clock::now());
}


void process_received_datagrams(int& remaining_batches)
{
    for (int i = 0; i < WINDOW_SIZE; i++) // sliding window
    {
        if (received_datagram[batch_index])
        {
            if (!batch_saved_to_file[batch_index]) // actual batch wasn't saved
            {
                remaining_batches --;
                output_file << batch_contents[batch_index]; // writing to file
                batch_saved_to_file[batch_index] = true;

                cout << (double)(N_BATCHES - remaining_batches) / (double)(N_BATCHES)*100 << "% done" << endl;
                if (remaining_batches == 0)
                {
                    break;
                }
            }

            if (last_byte_requested != N_BYTES_REQUESTED) // if we didn't get the whole message
            {                                             // prepare messages to send to the server
                received_datagram[batch_index] = false;
                batch_saved_to_file[batch_index] = false;
                int get_bytes_length = min(BATCH_SIZE, N_BYTES_REQUESTED - last_byte_requested);
                // datagram format: GET start length
                send_message[batch_index] = "GET " + to_string(last_byte_requested) + " " + to_string(get_bytes_length) + "\n";
                last_byte_requested += get_bytes_length;
            }

            batch_index = (batch_index + 1) % WINDOW_SIZE;
        }
        else // no datagram
        {
            break;
        }
    }
}

#endif
