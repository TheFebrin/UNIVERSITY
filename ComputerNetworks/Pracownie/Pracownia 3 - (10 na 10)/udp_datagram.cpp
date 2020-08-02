/*
Dawid
Dieu
302052
*/

#include "udp_datagram.hpp"

Datagram::Datagram()
{
	this->request_sent_time = 0;
	this->request = "";
	this->data = "";
	this->port = 0;
	this->sent = false;
}


Datagram::Datagram(double rst, string r, string d, int p)
{
	this->request_sent_time = rst;
	this-> request = r;
	this->data = d;
	this->port = p;
	this->sent = false;
}


int Datagram::get_port()
{
	return this->port;
}



double Datagram::get_request_sent_time()
{
	return this->request_sent_time;
}


string Datagram::get_request()
{
	return this->request;
}


string Datagram::get_data()
{
	return this->data;
}


bool Datagram::get_sent()
{
	return this->sent;
}


void Datagram::set_port(int new_port)
{
	this->port = new_port;
}


void Datagram::set_request_sent_time(double new_time)
{
	this->request_sent_time=new_time;
}


void Datagram::set_request(string new_request)
{
	this->request = new_request;
}


void Datagram::set_data(string new_data)
{
	this->data = new_data;
}

void Datagram::set_sent()
{
	this->sent = true;
}
