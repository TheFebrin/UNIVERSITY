/*
Dawid
Dieu
302052
*/

#include "UDP.hpp"
#include "udp_datagram.hpp"
#include "functions.hpp"

using namespace std;

#define WINDOW_SIZE 500
#define DATAGRAM_SIZE 1000

int main(int argc, char *argv[])
{
    /*
    Usage:
    $ make
    $ ./transport <IP_ADDRESS> <PORT> <OUTPUT_FILE> <BYTES>

    Note:
    If program doesn't create a file use `sudo`.
    */

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    if (argc != 5)
    {
        exit_with_error("args-error");
        return 0;
    }

    char * ip_address = argv[1];
    if(!check_if_good_ip(ip_address))
    {
        exit_with_error("ip-error");
        return 0;
    }

    auto UDP_protocol = UDP(WINDOW_SIZE, DATAGRAM_SIZE, argv);

    while( !UDP_protocol.transport_completed() )
    {
        UDP_protocol.save_data();     // save bits of data
        UDP_protocol.request_data();  // prepare GET requests to server
        UDP_protocol.send_requests(); // send those requests
        UDP_protocol.receive_data();  // receive data from server
    }

    UDP_protocol.close_file();

    return 0;
}
