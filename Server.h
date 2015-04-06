#pragma once

#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

using namespace boost::asio;

class CServerLi
{
private:
	io_service &ios;
	ip::tcp::acceptor acceptor;
	typedef boost::shared_ptr<ip::tcp::socket> sock_pt;
	sock_pt sock;

public:
	CServerLi(io_service& io):ios(io),acceptor(ios,ip::tcp::endpoint(ip::tcp::v4(),6689))
	,sock(new ip::tcp::socket(ios))
	{
		//start();
	}
	
	void start()
	{
		//sock_pt sock(new ip::tcp::socket(ios));
		acceptor.accept(*sock);
		//acceptor.async_accept(*sock,bind(&CServerLi::accept_handler,this,placeholders::error,sock));
		
		std::cout<<"Li:";
		std::cout<<sock->remote_endpoint().address()<<std::endl;
	}
	
	void accept_handler(const boost::system::error_code& ec,sock_pt sock)
	{
		if(ec)
		{
			return;
		}
		
		std::cout<<"client:";
		std::cout<<sock->remote_endpoint().address()<<std::endl;
		
		try   
		{ 
			while(true)
			{
				char data_[1024];
				sock->async_read_some(boost::asio::buffer(data_, 1024),
					bind(&CServerLi::read_handler, this,
					placeholders::error,
					placeholders::bytes_transferred));
				sock->async_write_some(buffer("hello asio"),bind(&CServerLi::write_handler,this,placeholders::error));
			
				boost::posix_time::time_duration td(0,0,1,0);
				boost::this_thread::sleep(td);
			}
		}
		catch (std::exception& e)   
		{   
			std::cerr << "Exception: " << e.what() << "/n";   
		}   
	}
	
	void read_handler(const boost::system::error_code&,size_t bytes_transferred)
	{
		//std::cout<<"send msg complete."<<std::endl;
		std::vector<char>str(100,0);
		sock->read_some(buffer(str));
	}
	
	void write_handler(const boost::system::error_code&)
	{
		//std::cout<<"send msg complete."<<std::endl;
		sock->write_some(buffer("hello Li"));
	}
	
	void write(std::string& str)
	{
		//std::cout<<"send msg complete."<<std::endl;
		//sock->write_some(buffer("hello Li"));
		sock->write_some(buffer(str));
	}
};

class CServerGao
{
private:
	io_service &ios;
	ip::tcp::acceptor acceptor;
	typedef boost::shared_ptr<ip::tcp::socket> sock_pt;
	sock_pt sock;

public:
	CServerGao(io_service& io):ios(io),acceptor(ios,ip::tcp::endpoint(ip::tcp::v4(),6690))
	,sock(new ip::tcp::socket(ios))
	{
		//start();
	}
	
	void start()
	{
		//sock_pt sock(new ip::tcp::socket(ios));
		acceptor.accept(*sock);
		//acceptor.async_accept(*sock,bind(&CServerGao::accept_handler,this,placeholders::error,sock));
		std::cout<<"Gao:";
		std::cout<<sock->remote_endpoint().address()<<std::endl;
	}
	
	void accept_handler(const boost::system::error_code& ec,sock_pt sock)
	{
		if(ec)
		{
			return;
		}
		
		std::cout<<"client:";
		std::cout<<sock->remote_endpoint().address()<<std::endl;
		
		while(true)
		{
			char data_[1024];
			sock->async_read_some(boost::asio::buffer(data_, 1024),
				bind(&CServerGao::read_handler, this,
				placeholders::error,
				placeholders::bytes_transferred));
			sock->async_write_some(buffer("hello asio"),bind(&CServerGao::write_handler,this,placeholders::error));
			
			boost::posix_time::time_duration td(0,0,1,0);
			boost::this_thread::sleep(td);
		}
	}
	
	void read_handler(const boost::system::error_code&,size_t bytes_transferred)
	{
		//std::cout<<"send msg complete."<<std::endl;
		std::vector<char>str(100,0);
		sock->read_some(buffer(str));
	}
	
	void write_handler(const boost::system::error_code&)
	{
		//std::cout<<"send msg complete."<<std::endl;
		sock->write_some(buffer("hello Gao"));
	}
};


class CServerClient
{
private:
	io_service &ios;
	ip::tcp::acceptor acceptor;
	typedef boost::shared_ptr<ip::tcp::socket> sock_pt;
	CServerLi serverLi;
	CServerGao serverGao;

public:
	CServerClient(io_service& io):ios(io),acceptor(ios,ip::tcp::endpoint(ip::tcp::v4(),6688))
	,serverLi(io)
	,serverGao(io)
	{
		serverLi.start();
		serverGao.start();
		start();
	}
	
	void start()
	{
		sock_pt sock(new ip::tcp::socket(ios));
		acceptor.async_accept(*sock,bind(&CServerClient::accept_handler,this,placeholders::error,sock));
	}
	
	void accept_handler(const boost::system::error_code& ec,sock_pt sock)
	{
		if(ec)
		{
			return;
		}
		
		start();
		
		std::cout<<"client:";
		std::cout<<sock->remote_endpoint().address()<<std::endl;
		
		while(true)
		{
			char data_[1024];
			sock->async_read_some(boost::asio::buffer(data_, 1024),
				bind(&CServerClient::read_handler, this,
				placeholders::error,
				placeholders::bytes_transferred));
			
			std::string recvStr(data_);
			std::cout<<"recive from "<<sock->remote_endpoint().address();
			std::cout<<recvStr<<std::endl;

			if(-1!=recvStr.find("proxy"))
			{
				std::string writeStr="client have a message for you,Li";
				serverLi.write(writeStr);
			}
			
			sock->async_write_some(buffer("hello client"),bind(&CServerClient::write_handler,this,placeholders::error));
			
			boost::posix_time::time_duration td(0,0,1,0);
			boost::this_thread::sleep(td);
		}
	}
	
	void read_handler(const boost::system::error_code&,size_t bytes_transferred)
	{
		//std::cout<<"send msg complete."<<std::endl;
	}
	
	void write_handler(const boost::system::error_code&)
	{
		std::cout<<"send msg complete."<<std::endl;
	}
};