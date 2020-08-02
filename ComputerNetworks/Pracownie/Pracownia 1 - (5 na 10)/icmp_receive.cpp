/*
Dawid
Dieu
302052
*/

#include "icmp_receive.hpp"



void receive_response(int &sockfd, set < tuple < string, int, int > > &IPs,
	vector < int > &times)
{
	struct sockaddr_in sender;
	u_int8_t buffer[IP_MAXPACKET];
	socklen_t sender_len = sizeof(sender);


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

        char sender_ip_str[20];
        inet_ntop(AF_INET, &(sender.sin_addr), sender_ip_str, sizeof(sender_ip_str));

		int time_elapsed = (clock() - t);
        times.push_back(time_elapsed);


		struct ip* ip_header = (struct ip*) buffer;
		u_int8_t* icmp_packet = buffer + 4 * ip_header->ip_hl;
	    struct icmp* icmp_header = ( struct icmp* )(icmp_packet);

		if (icmp_header->icmp_type  == ICMP_ECHOREPLY)
		{
			IPs.insert({sender_ip_str,
						icmp_header->icmp_hun.ih_idseq.icd_id,
						icmp_header->icmp_hun.ih_idseq.icd_seq}
			);
		}
	    else if (icmp_header->icmp_type  == ICMP_TIME_EXCEEDED)
		{
			icmp_packet += 8;
			icmp_packet += 4 * ((struct ip*) icmp_packet)->ip_hl;

			struct icmp* icmp_header_TLE = (struct icmp*) icmp_packet;
			IPs.insert({sender_ip_str,
						icmp_header_TLE->icmp_hun.ih_idseq.icd_id,
						icmp_header_TLE->icmp_hun.ih_idseq.icd_seq}
			);
	    }
		else
		{
			cout << "Unknown flag!" << endl;
		}
    }
}


void delete_bad_packages( set < tuple < string, int, int > > &IPs,
	vector < pair < int, int > > sent_ids, set < string > &valid_IPs)
{
	int i = 0;
	for(auto t: IPs)
	{
		string s;
		int ip_, seq_;
		tie(s, ip_, seq_) = t;

		if(ip_ == sent_ids[i].first and seq_ == sent_ids[i].second)
			valid_IPs.insert(s);

		i ++;
	}
}


void show_response(int ttl, set < string > valid_IPs,
	vector < int > times, bool &reached, string ip)
{
    cout << " " << ttl << ".  ";
    if(valid_IPs.size() == 0) // no responses
    {
        cout << "*" << endl;
    }
    else
    {
        int time = 0;
        if(times.size() == 3)
            time = accumulate(times.begin(), times.end(), 0.0) / 3.0;

        for(auto s: valid_IPs)
        {
            if(time == 0)
                cout << s << " " << "???" << endl;
            else
                cout << s << " " << time << "ms" << endl;

			if (s == ip) // we reached final IP
				reached = true;
        }
    }
}
