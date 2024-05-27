#pragma once

#include "boost/asio.hpp"

namespace ba = boost::asio;

class tcp_connection: public std::enable_shared_from_this<tcp_connection>
{
public:
	explicit tcp_connection(ba::ip::tcp::socket socket);
	void start();

private:
	void do_read();

	void readHeandler();

private:
	ba::ip::tcp::socket m_socket;
	std::array<char, 1024> m_buffer;
};

class server
{
public:
	server(ba::io_context& context, const ba::ip::port_type port);
	
private:
	void acceptClient();

private:
	ba::ip::tcp::acceptor m_acceptor;
};
