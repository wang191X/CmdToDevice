// RulesService.cpp : 实现文件
//

#include "stdafx.h"

#include "CmdToDevice.h"

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <fstream>
#include "RulesService.h"

using namespace boost::asio;

int logCount=0;
boost::mutex mtx;

std::string get_sysdate(void)
{
	struct tm today;
	time_t ltime;
	time( &ltime );
	char tmpbuf[50];
	_localtime64_s( &today, &ltime );
	strftime( tmpbuf, 50,"%Y年%m月%d日 %H:%M:%S", &today );
	std::string localtime(tmpbuf);
	return localtime;
}

void writeLog(std::string& message,CRulesService *pLpDlg)
{
	using namespace std;
	boost::mutex::scoped_lock lock(mtx);

	message=get_sysdate()+" "+message;
	ofstream ofile;
	ofile.open("ccol_log.txt",ios_base::app);
	ofile<<message<<endl;
	ofile.close();

	pLpDlg->mList1.InsertItem(logCount,"");
	pLpDlg->mList1.SetItemText(logCount,0,message.c_str());
	logCount++;
}	
	
class CServerCard1
{
private:
	io_service &ios;
	ip::tcp::acceptor acceptor;
	typedef boost::shared_ptr<ip::tcp::socket> sock_pt;
	sock_pt sock;
	//int logCount;

public:
	CRulesService *pLpDlg;

public:
	CServerCard1(io_service& io):ios(io),acceptor(ios,ip::tcp::endpoint(ip::tcp::v4(),6689))
	,sock(new ip::tcp::socket(ios))
	//,logCount(0)
	{
		//start();
	}

	// void writeLog(std::string& message)
	// {
		// using namespace std;	

		// ofstream ofile;
		// ofile.open("ccol_log.txt",ios_base::app);
		// ofile<<message<<endl;
		// ofile.close();

		// pLpDlg->mList1.InsertItem(logCount,"");
		// pLpDlg->mList1.SetItemText(logCount,0,message.c_str());
		// logCount++;
	// }	
	
	void start()
	{
		//sock_pt sock(new ip::tcp::socket(ios));
		acceptor.accept(*sock);
		//acceptor.async_accept(*sock,bind(&CServerCard1::accept_handler,this,placeholders::error,sock));
		
		//std::cout<<"Li:";
		//std::cout<<sock->remote_endpoint().address()<<std::endl;
		std::string message="卡1已连接";
		writeLog(message,pLpDlg);
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
					bind(&CServerCard1::read_handler, this,
					placeholders::error,
					placeholders::bytes_transferred));
				sock->async_write_some(buffer("hello asio"),bind(&CServerCard1::write_handler,this,placeholders::error));
			
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
		sock->write_some(buffer("hello"));
	}
	
	void write(std::string& str)
	{
		//std::cout<<"send msg complete."<<std::endl;
		//sock->write_some(buffer("hello Li"));
		try   
		{ 
			sock->write_some(buffer(str));
		}
		catch (std::exception& e)   
		{   
			//std::cerr << "Exception: " << e.what() << "/n"; 
			std::string message1(e.what());
			std::string message="卡1问题"+message1;
			writeLog(message,pLpDlg);
		}   
	}
};

class CServerCard2
{
private:
	io_service &ios;
	ip::tcp::acceptor acceptor;
	typedef boost::shared_ptr<ip::tcp::socket> sock_pt;
	sock_pt sock;
	//int logCount;

public:
	CRulesService *pLpDlg;

public:
	CServerCard2(io_service& io):ios(io),acceptor(ios,ip::tcp::endpoint(ip::tcp::v4(),6690))
	,sock(new ip::tcp::socket(ios))
	//,logCount(0)
	{
		//start();
	}

	// void writeLog(std::string& message)
	// {
		// using namespace std;	

		// ofstream ofile;
		// ofile.open("ccol_log.txt",ios_base::app);
		// ofile<<message<<endl;
		// ofile.close();

		// pLpDlg->mList1.InsertItem(logCount,"");
		// pLpDlg->mList1.SetItemText(logCount,0,message.c_str());
		// logCount++;
	// }	
	
	void start()
	{
		//sock_pt sock(new ip::tcp::socket(ios));
		acceptor.accept(*sock);
		//acceptor.async_accept(*sock,bind(&CServerCard2::accept_handler,this,placeholders::error,sock));
		//std::cout<<"Gao:";
		//std::cout<<sock->remote_endpoint().address()<<std::endl;
		std::string message="卡2已连接";
		writeLog(message,pLpDlg);
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
				bind(&CServerCard2::read_handler, this,
				placeholders::error,
				placeholders::bytes_transferred));
			sock->async_write_some(buffer("hello asio"),bind(&CServerCard2::write_handler,this,placeholders::error));
			
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
		sock->write_some(buffer("hello"));
	}
};

class CServerClient
{
private:
	io_service &ios;
	short port;
	ip::tcp::acceptor acceptor;
	typedef boost::shared_ptr<ip::tcp::socket> sock_pt;
	CServerCard1 serverCard1;
	CServerCard2 serverCard2;
	CWFCLPAPI wfclpapi;
	SSession sSession;
	//sock_pt sock;
	
	int max_length;
	char* pRecvBuff;
	int logCount;

public:
	CRulesService *pLpDlg;

public:
	CServerClient(io_service& io):ios(io)
		,port(6688)
		,acceptor(ios,ip::tcp::endpoint(ip::tcp::v4(),port))
		,serverCard1(io)
		,serverCard2(io)
		,max_length(1024*1024)
		//,sock(new ip::tcp::socket(ios))
		//,logCount(0)
	{
	}
	
	~CServerClient()
	{
		delete [] pRecvBuff;
	}
	
	void start()
	{
		initDevCon();
		initData();
		serverCard1.pLpDlg=pLpDlg;
		serverCard2.pLpDlg=pLpDlg;
		//serverCard1.start();
		//serverCard2.start();
		start1();
	}

	void start1()
	{
		sock_pt sock(new ip::tcp::socket(ios));
		acceptor.async_accept(*sock,bind(&CServerClient::accept_handler,this,placeholders::error,sock));
	}
	
	void initDevCon()
	{
		int ret=wfclpapi.connect(sSession);

		if(ret==-1)
		{
			return;
		}

		std::string message="设备已连接";
		writeLog(message,pLpDlg);
	}
	
	void initData()
	{
		pRecvBuff=new char[max_length];
	}

	// std::string get_sysdate(void)
	// {
		// struct tm today;
		// time_t ltime;
		// time( &ltime );
		// char tmpbuf[50];
		// _localtime64_s( &today, &ltime );
		// strftime( tmpbuf, 50,"%Y年%m月%d日 %H:%M:%S", &today );
		// std::string localtime(tmpbuf);
		// return localtime;
	// }

	std::string numToStr(int id)
	{
		using namespace std;

		stringstream strStream;
		strStream<<id;
		string message1 = strStream.str();

		return message1;
	}

	// void writeLog(std::string& message)
	// {
		// using namespace std;	

		// ofstream ofile;
		// ofile.open("ccol_log.txt",ios_base::app);
		// ofile<<get_sysdate()<<" "<<message<<endl;
		// ofile.close();

		// pLpDlg->mList1.InsertItem(logCount,"");
		// pLpDlg->mList1.SetItemText(logCount,0,message.c_str());
		// logCount++;
	// }	
	
	void accept_handler(const boost::system::error_code& ec,sock_pt sock)
	{
		if(ec)
		{
			std::string message1="未知";
			writeLog(message1,pLpDlg);
			return;
		}
		
		start1();

		std::string message=sock->remote_endpoint().address().to_string()+"客户端已连接";
		writeLog(message,pLpDlg);
		
		//std::cout<<"client:";
		//std::cout<<sock->remote_endpoint().address()<<std::endl;
		
		//while(true)
		//{
			sock->async_read_some(boost::asio::buffer(pRecvBuff,max_length),
				bind(&CServerClient::read_handler, this,
				placeholders::error,
				placeholders::bytes_transferred,sock));
			
			//std::string recvStr(data_);
			//std::cout<<"recive from "<<sock->remote_endpoint().address();
			//std::cout<<recvStr<<std::endl;

			//if(-1!=recvStr.find("proxy"))
			//{
			//	std::string writeStr="client have a message for you,Li";
			//	serverCard1.write(writeStr);
			//}
			
			//sock->async_write_some(buffer("hello client"),bind(&CServerClient::write_handler,this,placeholders::error,sock));
			
			//boost::posix_time::time_duration td(0,0,1,0);
			//boost::this_thread::sleep(td);
		//}
	}
	
	void read_handler(const boost::system::error_code& ec,size_t bytes_transferred,sock_pt sock)
	{
		if (ec)
		{
			std::string message1="客户端读问题";
			writeLog(message1,pLpDlg);
			return;
		}
		
		std::string ip=sock->remote_endpoint().address().to_string();
		int recv_len=bytes_transferred;

		if (pRecvBuff[0]>=ACL_ADD&&pRecvBuff[0]<=ACL_DELETE_FAILED)
		{
			int len=sizeof(SACL);
			int ruleCount=recv_len/len;
			SACL* psacl=new SACL[ruleCount];

			for (int i=0;i!=ruleCount;++i)
			{
				memcpy_s(&psacl[i],len,pRecvBuff+len*i,len);
			}

			for (int i=0;i!=ruleCount;++i)
			{
				if (psacl[i].cmdType==ACL_ADD)
				{
					wfclpapi.sacl=psacl[i];

					int ret=wfclpapi.uploadACL();

					if(ret==-1)
					{
						psacl[i].cmdType=ACL_ADD_FAILED;
						std::string message1="失败,命令类型：下发acl，id："+numToStr(psacl[i].id)+","+ip;
						writeLog(message1,pLpDlg);
						
						std::string writeStr="规则生效";
						//serverCard1.write(writeStr);
					}
					else
					{
						psacl[i].cmdType=ACL_ADD_SUCCESS;
						std::string message1="成功,命令类型：下发acl，id："+numToStr(psacl[i].id)+","+ip;
						writeLog(message1,pLpDlg);
						//message1.Format("命令类型：下发acl，id：%d，成功",psacl[i].id);
						//writeLog(message1,pLpDlg);
					}

				}
				else if (psacl[i].cmdType==ACL_DELETE)
				{
					int ret=wfclpapi.removeACL(psacl[i].id);

					if(ret==-1)
					{
						psacl[i].cmdType=ACL_DELETE_FAILED;
						std::string message1="失败,命令类型：删除acl，id："+numToStr(psacl[i].id)+","+ip;
						writeLog(message1,pLpDlg);
						//message1.Format("命令类型：删除acl，id：%d，失败",psacl[i].id);
						//writeLog(message1,pLpDlg);
					}
					else
					{
						psacl[i].cmdType=ACL_DELETE_SUCCESS;
						std::string message1="成功,命令类型：删除acl，id："+numToStr(psacl[i].id)+","+ip;
						writeLog(message1,pLpDlg);
						//message1.Format("命令类型：删除acl，id：%d，成功",psacl[i].id);
						//writeLog(message1,pLpDlg);
					}	
				}
			}

			char* pSendBuff=new char[recv_len];

			for (int i=0;i!=ruleCount;++i)
			{
				memcpy_s(pSendBuff+len*i, recv_len, (char*)&psacl[i], len );
			}

			sock->async_write_some(buffer(pSendBuff,recv_len),bind(&CServerClient::write_handler,this,placeholders::error,sock));
		}
		else if (pRecvBuff[0]>=XACL_ADD&&pRecvBuff[0]<=XACL_DELETE_FAILED)
		{
			int len=sizeof(SXACL);
			int ruleCount=recv_len/len;
			SXACL* psxacl=new SXACL[ruleCount];

			for (int i=0;i!=ruleCount;++i)
			{
				memcpy_s(&psxacl[i],len,pRecvBuff+len*i,len);
			}

			for (int i=0;i!=ruleCount;++i)
			{
				if (psxacl[i].cmdType==XACL_ADD)
				{
					wfclpapi.sxacl=psxacl[i];

					int ret=wfclpapi.uploadXACL();

					if(ret==-1)
					{
						psxacl[i].cmdType=XACL_ADD_FAILED;
						std::string message1="失败,命令类型：下发xacl，id："+numToStr(psxacl[i].id)+","+ip;
						writeLog(message1,pLpDlg);
						//message1.Format("命令类型：下发xacl，id：%d，失败",psxacl[i].id);
						//writeLog(message1,pLpDlg);
					}
					else
					{
						psxacl[i].cmdType=XACL_ADD_SUCCESS;
						std::string message1="成功,命令类型：下发xacl，id："+numToStr(psxacl[i].id)+","+ip;
						writeLog(message1,pLpDlg);
						//message1.Format("命令类型：下发xacl，id：%d，成功",psxacl[i].id);
						//writeLog(message1,pLpDlg);
					}


				}
				else if (psxacl[i].cmdType==XACL_DELETE)
				{
					int ret=wfclpapi.removeXACL(psxacl[i].id);

					if(ret==-1)
					{
						psxacl[i].cmdType=XACL_DELETE_FAILED;
						std::string message1="失败,命令类型：删除xacl，id："+numToStr(psxacl[i].id)+","+ip;
						writeLog(message1,pLpDlg);
						//message1.Format("命令类型：删除xacl，id：%d，失败",psxacl[i].id);
						//writeLog(message1,pLpDlg);
					}
					else
					{
						psxacl[i].cmdType=XACL_DELETE_SUCCESS;
						std::string message1="成功,命令类型：删除xacl，id："+numToStr(psxacl[i].id)+","+ip;
						writeLog(message1,pLpDlg);
						//message1.Format("命令类型：删除xacl，id：%d，成功",psxacl[i].id);
						//writeLog(message1,pLpDlg);
					}

				}
			}

			char* pSendBuff=new char[recv_len];

			for (int i=0;i!=ruleCount;++i)
			{
				memcpy_s(pSendBuff+len*i, recv_len, (char*)&psxacl[i], len );
			}

			sock->async_write_some(buffer(pSendBuff,recv_len),bind(&CServerClient::write_handler,this,placeholders::error,sock));
		}
		else if (pRecvBuff[0]>=PL_ADD&&pRecvBuff[0]<=PL_DELETE_FAILED)
		{
			int len=sizeof(SPL);
			int ruleCount=recv_len/len;
			SPL* pspl=new SPL[ruleCount];

			for (int i=0;i!=ruleCount;++i)
			{
				memcpy_s(&pspl[i],len,pRecvBuff+len*i,len);
			}

			for (int i=0;i!=ruleCount;++i)
			{
				if (pspl[i].cmdType==PL_ADD)
				{
					wfclpapi.spl=pspl[i];
					int ret=wfclpapi.uploadPL();

					if(ret==-1)
					{
						//message1.Format("命令类型：下发PL，id：%d，失败",pspl[i].id);

						pspl[i].cmdType=PL_ADD_FAILED;
						std::string message1="失败,命令类型：下发PL，id："+numToStr(pspl[i].id)+","+ip;
						writeLog(message1,pLpDlg);

						//writeLog(message1,pLpDlg);
					}
					else
					{
						//message1.Format("命令类型：下发PL，id：%d，成功",pspl[i].id);

						pspl[i].cmdType=PL_ADD_SUCCESS;
						std::string message1="成功,命令类型：下发PL，id："+numToStr(pspl[i].id)+","+ip;
						writeLog(message1,pLpDlg);

						//writeLog(message1,pLpDlg);
					}
				}
				else if (pspl[i].cmdType==PL_DELETE)
				{
					int ret=wfclpapi.removePL(pspl[i].id);

					if(ret==-1)
					{
						//message1.Format("命令类型：删除PL，id：%d，失败",pspl[i].id);

						pspl[i].cmdType=PL_DELETE_FAILED;
						std::string message1="失败,命令类型：删除PL，id："+numToStr(pspl[i].id)+","+ip;
						writeLog(message1,pLpDlg);

						//writeLog(message1,pLpDlg);
					}
					else
					{
						//message1.Format("命令类型：删除PL，id：%d，成功",pspl[i].id);

						pspl[i].cmdType=PL_DELETE_SUCCESS;
						std::string message1="成功,命令类型：删除PL，id："+numToStr(pspl[i].id)+","+ip;
						writeLog(message1,pLpDlg);

						//writeLog(message1,pLpDlg);
					}
				}
			}

			char* pSendBuff=new char[recv_len];

			for (int i=0;i!=ruleCount;++i)
			{
				memcpy_s(pSendBuff+len*i, recv_len, (char*)&pspl[i], len );
			}

			sock->async_write_some(buffer(pSendBuff,recv_len),bind(&CServerClient::write_handler,this,placeholders::error,sock));
		}
	}
	
	void write_handler(const boost::system::error_code& error,sock_pt sock)
	{
		if (error)
		{
			std::string message1="客户端写问题";
			writeLog(message1,pLpDlg);
			return;
		}
		std::cout<<"send msg complete."<<std::endl;

		sock->async_read_some(boost::asio::buffer(pRecvBuff,max_length),
			bind(&CServerClient::read_handler, this,
			placeholders::error,
			placeholders::bytes_transferred,sock));
	}
};


// CRulesService 对话框

IMPLEMENT_DYNAMIC(CRulesService, CDialog)

CRulesService::CRulesService(CWnd* pParent /*=NULL*/)
: CDialog(CRulesService::IDD, pParent)
{

}

CRulesService::~CRulesService()
{
}

void CRulesService::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mList1);
}

BEGIN_MESSAGE_MAP(CRulesService, CDialog)
	ON_BN_CLICKED(IDStart, &CRulesService::OnBnClickedStart)
	ON_BN_CLICKED(IDStop, &CRulesService::OnBnClickedStop)
	ON_BN_CLICKED(IDClrLog, &CRulesService::OnBnClickedClrlog)
END_MESSAGE_MAP()

//typedef boost::shared_ptr<tcp::socket> socket_ptr;

//void session(socket_ptr sock)
//{
//	const int max_length = 1024;
//
//	try
//	{
//		for (;;)
//		{
//			char data[max_length];
//
//			boost::system::error_code error;
//			size_t length = sock->read_some(boost::asio::buffer(data), error);
//			if (error == boost::asio::error::eof)
//				break; // Connection closed cleanly by peer.
//			else if (error)
//				throw boost::system::system_error(error); // Some other error.
//
//			boost::asio::write(*sock, boost::asio::buffer(data, length));
//		}
//	}
//	catch (std::exception& e)
//	{
//		std::cerr << "Exception in thread: " << e.what() << "\n";
//	}
//}

//void toSerialize(std::vector<SACL>& sacls_,std::string& outbound_data_)
//{
//	// Serialize the data first so we know how large it is.
//	std::ostringstream archive_stream;
//	boost::archive::text_oarchive archive(archive_stream);
//	archive << sacls_;
//	outbound_data_ = archive_stream.str();
//}
//
//void fromSerialize(std::vector<char>& recvBuff,std::vector<SACL>& sacls_)
//{
//	std::string archive_data(&recvBuff[0], recvBuff.size());
//	std::istringstream iarchive_stream(archive_data);
//	boost::archive::text_iarchive iarchive(iarchive_stream);
//	iarchive >> sacls_;
//}

// int logCount=0;

// void writeLog(CString& info,CRulesService *pLpDlg)
// {
		// pLpDlg->mList1.InsertItem(logCount,"");
		// pLpDlg->mList1.SetItemText(logCount,0,info);
		// logCount++;
// }

// CRulesService 消息处理程序
void recvMessage(LPVOID lpParameter)
{
	CRulesService *pLpDlg=((CRulesService *)(lpParameter));

	io_service ios;
	CServerClient server(ios);
	server.pLpDlg=pLpDlg;
	server.start();
	ios.run();
}

void CRulesService::OnBnClickedStart()
{
    //CWFCLPAPI wfclpapi;
	//SSession ss;
	//wfclpapi.connect(ss);
	//wfclpapi.uploadXACL();


	boost::thread t1(recvMessage,(LPVOID)this);
	// TODO: 在此添加控件通知处理程序代码

}

void CRulesService::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
}



BOOL CRulesService::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	mList1.InsertColumn(0,"消息",LVCFMT_LEFT,500,0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CRulesService::OnBnClickedClrlog()
{
	// TODO: 在此添加控件通知处理程序代码
	mList1.DeleteAllItems();
	logCount=0;
}
