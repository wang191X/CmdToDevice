#include "StdAfx.h"
#include "SocketService.h"

CSocketService::CSocketService(void)
{
}

CSocketService::~CSocketService(void)
{
}

typedef boost::shared_ptr<tcp::socket> socket_ptr;

void CSocketService::session(socket_ptr sock)
{
	try
	{
		for (;;)
		{
			char data[max_length];

			boost::system::error_code error;
			size_t length = sock->read_some(boost::asio::buffer(data), error);
			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			boost::asio::write(*sock, boost::asio::buffer(data, length));
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception in thread: " << e.what() << "\n";
	}
}

void CSocketService::server(boost::asio::io_service& io_service, short port)
{
	tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
	for (;;)
	{
		socket_ptr sock(new tcp::socket(io_service));
		a.accept(*sock);
		boost::thread t(boost::bind(session, sock));
	}
}
