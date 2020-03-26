/*
Dawid
Dieu
302052
*/

#include "icmp_send.hpp"

void print_as_bytes (unsigned char* buff, ssize_t length)
{
	for (ssize_t i = 0; i < length; i++, buff++)
		printf ("%.2x ", *buff);
}


u_int16_t compute_icmp_checksum (const u_int16_t *buff, int length)
{
	u_int32_t sum;
	const u_int16_t* ptr = buff;
	assert (length % 2 == 0);
	for (sum = 0; length > 0; length -= 2)
		sum += *ptr++;
	sum = (sum >> 16) + (sum & 0xffff);
	return (u_int16_t)(~(sum + (sum >> 16)));
}


void send_packages(int &sockfd, char *ip, sockaddr_in &dest, int &ttl, icmp &header)
{
	socklen_t sender_len = sizeof(dest);
	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(0);
    inet_pton(AF_INET, ip, &dest.sin_addr);

    header.icmp_type = ICMP_ECHO;
    header.icmp_code = 0;
    header.icmp_hun.ih_idseq.icd_id = getpid();
    header.icmp_hun.ih_idseq.icd_seq = 0;
    header.icmp_cksum = 0;
    header.icmp_cksum = compute_icmp_checksum ((u_int16_t*)&header, sizeof(header));
    setsockopt (sockfd, IPPROTO_IP, IP_TTL, (char *)&ttl, sizeof(ttl));

    for(int i = 0; i < 3; i ++)
    {
        ssize_t bytes_sent = sendto (
            sockfd,
            &header,
            sizeof(header),
            0,
            (struct sockaddr*)&dest,
            sender_len
        );

        if(bytes_sent  < 0)
        {
            perror("Socket failure!");
            exit(EXIT_FAILURE);
        }
    }
}
