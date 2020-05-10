/*
Dawid
Dieu
302052
*/

#pragma once
#ifndef send

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <bits/stdc++.h>

#include "constants.hpp"
#include "functions.hpp"
using namespace std;
using namespace chrono;


void send_messages(int sockfd, char *ip_address)
{
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, ip_address, &server_address.sin_addr);

    for (int i = 0; i < WINDOW_SIZE; i++)
    {
        // we want to make sure that server had some time to respond
        bool server_could_respond = system_clock::now() - message_send_time[i] > milliseconds(200);

        if (!received_datagram[i] and server_could_respond)
        {
            message_send_time[i] = system_clock::now();
            ssize_t message_len = send_message[i].length();

            if (sendto(
                    sockfd,
                    send_message[i].c_str(),
                    message_len,
                    0,
                    (struct sockaddr *) &server_address,
                    sizeof(server_address)) != message_len
            ){
                handle_error("sendto-error");
            }
        }
    }
}

#endif
