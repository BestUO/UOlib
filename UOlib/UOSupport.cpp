#include "UOSupport.h"
#include <boost/lexical_cast.hpp>  
#include <boost/bind.hpp>
#include <errno.h>
//////////////////UOSupport::UOFile/////////////////////////////////////////////
UOSupport::UOFile::UOFile()
{
}

UOSupport::UOFile::~UOFile()
{
}

void UOSupport::UOFile::WriteFile(std::string Path,char *data, int len)
{
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp,Path.c_str(), "wb");
	if (!err)
		fwrite(data, len,1, fp);
	fclose(fp);
}

int UOSupport::UOFile::ReadFile(std::string Path, char *data)
{
	int len = 0;
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, Path.c_str(), "wb");
	if (!err)
		len = fread(data, 1,10240, fp);
	fclose(fp);
	return len;
}

/////////////////////////////////////////UDP_Client//////////////////////////////
UDPClientSocketUO::UDPClientSocketUO(std::string IP, int rport) :m_udpsock(m_io_service)
{
	m_udpsock.open(boost::asio::ip::udp::v4());
	IniSocket(IP, rport);
}

UDPClientSocketUO::~UDPClientSocketUO()
{
	m_udpsock.close();
}

bool UDPClientSocketUO::IniSocket(std::string IP, int rport)
{
	try
	{
		m_remote_endpoint = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(IP), rport);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

bool UDPClientSocketUO::SynchroUDP_Send(const std::string &msg)
{
	try
	{
		m_udpsock.send_to(boost::asio::buffer(msg, msg.size()), m_remote_endpoint);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return false;
	}
	return true;
}

std::string UDPClientSocketUO::SynchroUDP_Receive()
{
	char ch[100] = { 0 };
	try
	{
		int len = m_udpsock.receive_from(boost::asio::buffer(ch), m_remote_endpoint);
		std::string str(ch, len);
		return str;
	}
	catch (const std::exception& e)
	{
		auto tmp = e.what();
		return "";
	}
}
////////////////////////////TCP Client///////////////////////////////////////
TCPClientUO::TCPClientUO(std::string IP, int port):m_socket(m_ios)
{
	iniSynchroTCP_Client(IP, port);
}

TCPClientUO::~TCPClientUO()
{
	m_socket.close();
}

bool TCPClientUO::iniSynchroTCP_Client(std::string IP, int port)
{
	try
	{
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(IP), port);
		m_socket.connect(endpoint);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

bool TCPClientUO::SynchroTCP_Send(const std::string msg)
{
	size_t len = msg.size();
	try
	{
		while (len > 0)
		{
			size_t pos = m_socket.write_some(boost::asio::buffer(msg.data() + msg.size() - len,len));
			len -= pos;
		}	
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}
	
std::string TCPClientUO::SynchroTCP_Recv()
{
	char buf[128] = {0};
	try
	{
		int len  = m_socket.read_some(boost::asio::buffer(buf));
		std::string str(buf,len);
		return str;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return "";
	}
}

/////////////////////////////////////////UDP_Server//////////////////////////////
UDPServerSocketUO::UDPServerSocketUO() : m_udpsock(m_io_service)//m_udpsock(m_io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 6677))
{
	m_pMQ = nullptr;
}

UDPServerSocketUO::~UDPServerSocketUO()
{
	m_udpsock.close();
}

void UDPServerSocketUO::runserver(int port)
{
	boost::asio::ip::udp::endpoint ep(boost::asio::ip::udp::v4(), port);
	m_udpsock.open(ep.protocol());
	m_udpsock.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_udpsock.bind(ep);

	Start_Receive();
	boost::thread([&]() { m_io_service.run(); });
}

void UDPServerSocketUO::Start_Receive()
{
	m_udpsock.async_receive_from(
		boost::asio::buffer(m_buf), m_remote_endpoint,
		boost::bind(&UDPServerSocketUO::Handle_Receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void UDPServerSocketUO::Handle_Receive(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error || error == boost::asio::error::message_size)
	{
		//std::cout << "received from<" << m_remote_endpoint.address().to_string() << ":" << m_remote_endpoint.port() << ">" << std::endl;
		std::string str = MakePacket(m_buf, bytes_transferred);
		std::cout << str << std::endl;
		memset(m_buf, 0, BUFSIZE);
		if (str.size() > 0 && m_pMQ)
			m_pMQ->putPacket(str);
		Start_Receive();
	}
}

std::string UDPServerSocketUO::MakePacket(char* data, int len)
{
	m_str.append(data, len);
	const char* d = m_str.data();
	//if ()
	//{
	//}
	//else
	//{
	//}
	std::string s = m_str.substr(0, len);
	m_str.erase(0, len);
	return s;
}

/////////////////////////////////TCP Server///////////////////////////////
TCPServerUO::TCPServerUO() :m_acc(m_ios)//, m_sock(m_ios)
{
	m_breaded = false;
	m_pMQ = nullptr;
}

TCPServerUO::~TCPServerUO()
{
	m_ios.stop();
}

void TCPServerUO::runserver(int port)
{
	//runSynchroTCP_Server(port);
	runAsyncTCP_Server(port);
}

void TCPServerUO::runSynchroTCP_Server(const int &port)
{
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(),port);

	m_acc.open(ep.protocol());
	m_acc.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_acc.bind(ep);
	m_acc.listen();
	
	while (true)
	{
		boost::shared_ptr<boost::asio::ip::tcp::socket> client_socket(new boost::asio::ip::tcp::socket(m_ios));
		m_acc.accept(*client_socket);

		boost::thread(boost::bind(&TCPServerUO::client_session, this, client_socket));
	}
}

void TCPServerUO::client_session(const boost::shared_ptr<boost::asio::ip::tcp::socket> sock)
{
	while (true)
	{
		char data[1460] = { 0 };
		try
		{
			size_t len = sock->read_some(boost::asio::buffer(data));
			if (len == 0)
			{
				sock->close();
				break;
			}
			else if (len > 0)
			{
				//std::cout << "form IP:" << sock->remote_endpoint().address() << " " << "port:" << sock->remote_endpoint().port() << std::endl;
				std::string str = MakePacket(data, len);
				if (str.size() > 0 && m_pMQ)
					m_pMQ->putPacket(str);
				else
					continue;
			}
		}
		catch (const boost::system::system_error e)
		{
			sock->close();
			std::cout << e.what() << std::endl;
			break;
		}
	}
}

std::string TCPServerUO::MakePacket(char* data,int len)
{
	m_str.append(data, len);
	const char* d = m_str.data();
	//if ()
	//{
	//}
	//else
	//{
	//}
	std::string s = m_str.substr(0, len);
	m_str.erase(0, len);
	return s;
}

void TCPServerUO::runAsyncTCP_Server(const int &port)
{
	iniAsyncTCP_Server(port);
	start_accept();
	for (size_t i = 0; i < 2; i++)
		boost::thread([&]() { m_ios.run(); });
		//boost::thread(boost::bind(&TCPServerUO::runthread,this));
	//m_ios.run();
}

void TCPServerUO::iniAsyncTCP_Server(const int &port)
{
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port);
	m_acc.open(ep.protocol());
	m_acc.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_acc.bind(ep);
	m_acc.listen();
}

void TCPServerUO::start_accept()
{
	try
	{
		share_ptr_sock sock(new boost::asio::ip::tcp::socket(m_ios));
		m_acc.async_accept(*sock, boost::bind(&TCPServerUO::handle_accept, this, sock, _1));
	}
	catch (const boost::system::system_error& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TCPServerUO::handle_accept(share_ptr_sock sock, const boost::system::error_code &err)
{
	if (err)
		return;
	else
		client_session2(sock);
	start_accept();
}

void TCPServerUO::client_session2(share_ptr_sock sock)
{
	memset(m_buf, 0, 1460);
	try
	{
		//std::cout << "form IP:" << sock->remote_endpoint().address() << " " << "port:" << sock->remote_endpoint().port() << std::endl;
		//boost::asio::async_read(*sock, boost::asio::buffer(m_str), boost::bind(&TCPServerUO::handle_read, this, sock, _1, _2));
		sock->async_read_some(boost::asio::buffer(m_buf), boost::bind(&TCPServerUO::handle_read, this, sock, _1, _2));
		//boost::asio::deadline_timer t(m_ios,boost::posix_time::seconds(10));
		//t.async_wait(boost::bind(&TCPServerUO::deadline_handler,this, sock, _1));
	}
	catch (const boost::system::system_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TCPServerUO::handle_read(share_ptr_sock sock,const boost::system::error_code &err, const std::size_t &bytes_transferred)
{
	if (!err) 
	{
		if (bytes_transferred > 0 && m_pMQ)
		{
			std::string str = MakePacket(m_buf, bytes_transferred);
			memset(m_buf, 0, BUFSIZE);
			if (str.size() > 0 && m_pMQ)
				m_pMQ->putPacket(str);
			client_session2(sock);
			m_breaded = true;
		}
	}
	else 
	{
		sock->close();
		std::cout << err.message() << std::endl;
	}
}

//void TCPServerUO::deadline_handler(share_ptr_sock &sock,const boost::system::error_code &err)
//{
//	if (!m_breaded)
//	{
//		std::cout << "out of time" << std::endl;
//		m_sock.close();
//	}
//}


/////////////////////////////////////////////Adaptor Class//////////////////////////////////////////////
//Adaptor::Adaptor(MSGqueue<STRPACKET> *in):m_in(in)
//{
//	//m_thrd = boost::thread(boost::bind(&PacketUO::SubmitPacket, &PACKET, m_pSocket, m_cmd, m_allsubgrp));
//	//m_thrd.interrupt();
//}

//Adaptor::~Adaptor()
//{
//
//}
//
//void Adaptor::SendToSocket()
//{
//	while (true)
//	{
//		if (m_in->haspacket())
//		{
//			STRPACKET* tmp;
//			while ((tmp = GetFromMQ(m_in)) != NULL)
//			{
//				////deal with packet SerializePacket(*tmp);
//				//send
//			}
//		}
//	}
//}
//
//void Adaptor::SendToMQ()
//{
//	while (true)
//	{
//		if (m_in->haspacket())
//		{
//			STRPACKET* tmp;
//			while ((tmp = GetFromMQ(m_in)) != NULL)
//			{
//				//	dela with Packet PutToMQ(tmp)
//			}
//		}
//		break;
//	}
//}

//STRPACKET* Adaptor::GetFromMQ(MSGqueue<STRPACKET>* in)
//{
//	if (in->getsize())
//		return in->getPacket();
//	else
//		return NULL;
//}
//
//std::string Adaptor::SerializePacket(const STRPACKET &packet)
//{
//	std::ostringstream os;
//	boost::archive::binary_oarchive oa(os);
//	oa << packet;
//	return os.str();
//}
//
//STRPACKET Adaptor::UnSerializePacket(const std::string str)
//{
//	STRPACKET packet;
//	std::istringstream is(str);
//	boost::archive::binary_iarchive ia(is);
//	ia >> packet;//从一个保存序列化数据的string里面反序列化，从而得到原来的对象。  
//	return packet;
//}
//
//void Adaptor::PutToMQ(STRPACKET *packet)
//{
//	m_out->putPacket(*packet);
//}