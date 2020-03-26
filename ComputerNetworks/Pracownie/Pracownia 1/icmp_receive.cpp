/*
Dawid
Dieu
302052
*/

#include "icmp_receive.hpp"

void receive_response(int &sockfd, sockaddr_in &dest, bool &reached, set < string > &IPs,
	vector < int > &times, u_int8_t buffer[], sockaddr_in &sender, char *ip)
{
	socklen_t sender_len = sizeof(dest);
	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(0);

	// https://stackoverflow.com/questions/977684/how-can-i-express-10-milliseconds-using-timeval
	int milliseconds = 1000 / 3; // 1/3 second per package
    struct timeval tv;
    tv.tv_sec = milliseconds / 1000; // maximum timeout in seconds
    tv.tv_usec = (milliseconds % 1000) * 1000; // maximum timeout in microseconds
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

    for(int i = 0; i < 3; i ++)
    {
        double t = clock();

        ssize_t packet_len = recvfrom (
            sockfd,
            buffer,
            IP_MAXPACKET,
            0,
            (struct sockaddr*)&sender,
            &sender_len
        );

        if (packet_len < 0)
            continue;

        int time_elapsed = (clock() - t);
        char sender_ip_str[20];

        inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));
        IPs.insert(sender_ip_str);
        times.push_back(time_elapsed);

        if (strcmp (sender_ip_str, ip) == 0) // we reached final IP
            reached = true;
    }
}


void show_response(int ttl, set < string > IPs, vector < int > times)
{
    cout << " " << ttl << ".  ";
    if(IPs.size() == 0) // no responses
    {
        cout << "*" << endl;
    }
    else
    {
        int time = 0;
        if(times.size() == 3)
            time = accumulate(times.begin(), times.end(), 0.0) / 3.0;

        for(auto s: IPs)
        {
            if(time == 0)
                cout << s << " " << "???" << endl;
            else
                cout << s << " " << time << "ms" << endl;
        }
    }
}
