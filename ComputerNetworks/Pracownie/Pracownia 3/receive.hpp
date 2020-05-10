/*
Dawid
Dieu
302052
*/

#pragma once
#ifndef receive

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <bits/stdc++.h>

#include "constants.hpp"
#include "functions.hpp"

using namespace std;
using namespace chrono;

int get_ready(int sockfd)
{
    fd_set descriptors;
    FD_ZERO(&descriptors);
    FD_SET(sockfd, &descriptors);

    struct timeval tv;
    tv.tv_sec = TIMEOUT_SEC;
    tv.tv_usec = TIMEOUT_USEC;
    int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);

    if (ready < 0)
    {
        handle_error("select-error");
    }

    if (ready == 0)  // timeout
    {
        return 0;
    }

    return ready;
}


void receive_data(int sockfd)
{
    struct sockaddr_in  sender;
    socklen_t           sender_len = sizeof(sender);
    char                buffer[BUFFER_SIZE];
    char                sender_ip_str[20];

    if(get_ready(sockfd) == 0)
    {
        return; // timeout
    }

    while (true)
    {
        ssize_t datagram_len = recvfrom(
            sockfd,
            buffer,
            BUFFER_SIZE,
            MSG_DONTWAIT,
            (struct sockaddr *)&sender,
             &sender_len
        );

        if (datagram_len < 0)
        {
            break;
        }

        inet_ntop(
            AF_INET,
            &(sender.sin_addr),
            sender_ip_str,
            sizeof(sender_ip_str)
        );

        bool wrong_ip = (string)sender_ip_str != (string)ip_address;
        bool wrong_port = (port != ntohs(sender.sin_port));
        if (wrong_ip or wrong_port) // got message from wrong ip / port
        {
            continue;
        }

		/* Extracting data from server response */
        string response(buffer, datagram_len);
        int x = response.find('\n');
        string message = "GET" + response.substr(4, x - 3);
        string content = response.substr(x + 1);

        for (int i = 0; i < WINDOW_SIZE; i++)
        {
            if (send_message[i] == message and !received_datagram[i])
            {
                batch_contents[i] = content;
                batch_saved_to_file[i] = false;
                received_datagram[i] = true;
            }
        }
    }
}

#endif
