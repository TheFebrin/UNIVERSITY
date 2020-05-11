/*
Dawid
Dieu
302052
*/

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <bits/stdc++.h>

#include "constants.hpp"
#include "functions.hpp"
#include "send.hpp"
#include "receive.hpp"

using namespace std;
using namespace chrono;



int main(int argc, char *argv[])
{
    /*
    Note:
    If program doesn't create a file use `sudo`.
    */

    if (argc != 5)
    {
        handle_error("args-error");
        return 0;
    }

    ip_address = argv[1];
    if(!check_if_good_ip(ip_address))
    {
        handle_error("ip-error");
        return 0;
    }

    port = atoi(argv[2]);
    output_file.open(argv[3],  std::ofstream::out);
    N_BYTES_REQUESTED = atoi(argv[4]);

    N_BATCHES = (N_BYTES_REQUESTED + BATCH_SIZE  - 1) / BATCH_SIZE ;
    remaining_batches = N_BATCHES;

    int sockfd = init_socket();
    init_vectors();

    cout << setprecision(3) << fixed;
    cout << "0% done" << endl;

    while (remaining_batches > 0)
    {
        process_received_datagrams(remaining_batches);
        send_messages(sockfd, ip_address);
        receive_data(sockfd);
    }

    output_file.close(); // close file
    if (close(sockfd) < 0)
    {
        handle_error("close-error");
    }

    return 0;
}
