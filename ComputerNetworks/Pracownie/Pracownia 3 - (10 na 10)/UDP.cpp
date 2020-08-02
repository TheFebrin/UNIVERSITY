/*
Dawid
Dieu
302052
*/

#include "UDP.hpp"

UDP::UDP(){}


UDP::~UDP(){}


UDP::UDP(int window_size, int datagram_size, char* argv[])
{
	this->WINDOW_SIZE = window_size;
	this->DATAGRAM_SIZE = datagram_size;

	this->ip_address = argv[1];
	this->port = atoi(argv[2]);
	this->output_file.open(argv[3]);

	this->N_BYTES_REQUESTED = atoi(argv[4]);
	this->N_DATAGRAMS_NEEDED = (this->N_BYTES_REQUESTED + this->DATAGRAM_SIZE - 1) / this->DATAGRAM_SIZE;

	this->sockfd = init_socket();
}





int UDP::init_socket()
{
	bzero(&this->server_addr, sizeof(this->server_addr));
	this->server_addr.sin_family = AF_INET;
	this->server_addr.sin_port = htons(this->port);
	inet_pton(AF_INET, this->ip_address, &this->server_addr.sin_addr);

    int sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd < 0)
    {
        exit_with_error("socket-error");
    }

    return sfd;
}


bool UDP::transport_completed()
{
	// cout << "WINDOW SIZE / MESSAGES WAITING " << this->Datagrams.size() << endl;
	return this->n_datagrams_saved * DATAGRAM_SIZE >= this->N_BYTES_REQUESTED;
}


void UDP::request_data()
{
	/* Looking for empty datagrams that can be filled with a new requests. */

	while((int)Datagrams.size() < WINDOW_SIZE and this->id_datagram_sent * DATAGRAM_SIZE < this->N_BYTES_REQUESTED)
	{
		int n_bytes_saved = this->id_datagram_sent * DATAGRAM_SIZE;
		int requested_data_size = min(DATAGRAM_SIZE, this->N_BYTES_REQUESTED - n_bytes_saved);

		/* datagram request format: GET start length */
		string request = "GET " + to_string(this->id_datagram_sent * DATAGRAM_SIZE) + " " + to_string(requested_data_size) + "\n";

		auto datagram = Datagram(clock(), request, "", this->port);
		this->Datagrams[this->id_datagram_sent] = datagram;

		this->request_to_datagram_id[this->id_datagram_sent * DATAGRAM_SIZE] = this->id_datagram_sent;
		this->not_received.insert(this->id_datagram_sent);

		this->id_datagram_sent += 1;
	}
}


void UDP::send_requests()
{
	for(auto id: this->not_received)
	{
		auto datagram = this->Datagrams[id];

		double time = clock();
		string request = datagram.get_request();
		ssize_t request_size = request.size();

		double wait = 50; // time in ms
		bool waited = time - datagram.get_request_sent_time() > wait;
		bool valid_request = request_size > 0;
		bool server_responed = datagram.get_data().size() > 0;

		if (valid_request and (waited or !datagram.get_sent()) and !server_responed)
		{
			if (sendto(
					this->sockfd,
					request.c_str(),
					request_size,
					0,
					(struct sockaddr *) &this->server_addr,
					sizeof(this->server_addr)) < 0
			){
				exit_with_error("sendto-error");
			}
			this->Datagrams[id].set_sent();
			this->Datagrams[id].set_request_sent_time(time);
		}

		/*
			Here sockaddr_in server_addr will contain IP address, port etc...
			of the server that we want to take data from.
		*/
	}
}




void UDP::receive_data()
{
	/* When request are sent we collect all responses from the server.        */
	/* To speed up the process we maitain a map from requests to datagrams ids.       */

	socklen_t           sender_len = sizeof(this->server_addr);
	char                buffer[BUFFER_SIZE];
	char                received_from_ip[20];
	fd_set 				descriptors;

    FD_ZERO(&descriptors);
    FD_SET(this->sockfd, &descriptors);


	// https://stackoverflow.com/questions/977684/how-can-i-express-10-milliseconds-using-timeval
	int milliseconds = 1000;
	struct timeval tv;
	tv.tv_sec = milliseconds / 1000; // maximum timeout in seconds
	tv.tv_usec = (milliseconds % 1000) * 1000; // maximum timeout in microseconds

    int ready = select(this->sockfd + 1, &descriptors, NULL, NULL, &tv);

    if (ready < 0)
    {
        exit_with_error("select-error");
    }
    else if (ready == 0)  // timeout
    {
        return;
    }
	else // we take the data from the server_addr
	{
		int server_response_len = 0;
		do {
			server_response_len = recvfrom(
	            this->sockfd,
	            buffer,
	            BUFFER_SIZE,
	            MSG_DONTWAIT,
	            (struct sockaddr *)&this->server_addr,
	         	&sender_len
        	);

			/*
				Here sockaddr_in server_addr will contain IP address, port etc...
				of the server that we received data from.

				We need to check if it's the same server that we send our request to.
			*/

			inet_ntop(
	            AF_INET,
	            &(this->server_addr.sin_addr),
	            received_from_ip,
	            sizeof(received_from_ip)
        	);

			bool good_ip = received_from_ip == (string)this->ip_address;
			bool good_port = ntohs(this->server_addr.sin_port) == this->port;
			if(good_ip and good_port and server_response_len > 8)
			{
				/*
					We are sure that this is the data we asked for.
					Begin extraction.

					Example data format:
					DATA 0 10
					��K���{��
				 */
				string data(buffer, server_response_len);
				if(data.find("DATA ") > data.size())
				{
					continue;
				}

				int beg_of_data = data.find('\n') + 1;

				string request = data.substr(0, beg_of_data);
				data = data.substr(beg_of_data, server_response_len);

				int space = request.find(" ", 5);
				int bytes_from = stoi(request.substr(5, space - 5));
				int datagram_id = this->request_to_datagram_id[bytes_from];

				if (datagram_id >= this->n_datagrams_saved) // we didn't saved it yet
				{
					this->Datagrams[datagram_id].set_data(data);
					this->Datagrams[datagram_id].set_request("");
					this->not_received.erase(bytes_from / DATAGRAM_SIZE);
				}
			}

		} while(server_response_len > 0);
	}
}


void UDP::save_data()
{
	/* Writing to file contents of following datagrams. */

	while( true )
	{
		auto datagram = this->Datagrams[this->n_datagrams_saved];
		if(datagram.get_data().size() > 0) 			     //  there is some data to be saved
		{
			this->output_file << datagram.get_data();       // write data to file
			cout << setprecision(3) << fixed << ((double)(this->n_datagrams_saved + 1) / this->N_DATAGRAMS_NEEDED) * 100 << "% done" << endl;

			this->Datagrams.erase(this->n_datagrams_saved);
			this->n_datagrams_saved ++;
		}
		else
		{
			/* We have to break and wait for this chunk of data to arrive */
			break;
		}
	}
}


void UDP::close_file()
{
	// cout << "Closing file and socket!" << endl;
	this->output_file.close();

	if (close(sockfd) < 0) // close socket
    {
        exit_with_error("close-error");
    }
}
