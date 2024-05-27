#include "server.h"
#include <iostream>

server::server(ba::io_context& context, const ba::ip::port_type port)
	: m_acceptor(context, ba::ip::tcp::endpoint(ba::ip::tcp::v4(), port))
{
	acceptClient();
}

void server::acceptClient()
{
	m_acceptor.async_accept(
		[this](const boost::system::error_code& error, boost::asio::ip::tcp::socket peer) {
			if (!error.failed()) {
				std::make_shared<tcp_connection>(std::move(peer))->start();				
			}
			else {
				std::cerr << "Failed to connect: " << error.message() << std::endl;
			}
			acceptClient();
		}
	);
}

tcp_connection::tcp_connection(ba::ip::tcp::socket socket)
	:m_socket(std::move(socket))
{
}

void tcp_connection::start()
{
	do_read();
}

void tcp_connection::do_read()
{
	auto self = shared_from_this();
	m_socket.async_read_some(
		ba::buffer(m_buffer),
		[self](const boost::system::error_code& error, std::size_t bytes_transferred) {
			self->readHeandler();
		}
	);
}

void tcp_connection::readHeandler()
{

}
