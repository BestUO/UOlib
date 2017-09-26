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
	boost::asio::ip::udp::resolver resolver(m_io_service);
	boost::asio::ip::udp::resolver::query query(IP, boost::lexical_cast<std::string>(rport));
	m_remote_endpoint = *resolver.resolve(query);

	m_udpsock.open(boost::asio::ip::udp::v4()); 
}

UDPClientSocketUO::UDPClientSocketUO(std::string IP, int lport, int rport)/*: m_udpsock(m_io_service)*/ : m_udpsock(m_io_service, boost::asio::ip::udp::udp::endpoint(boost::asio::ip::udp::udp::v4(), lport))
{
	IniSynchroUDP_Client(IP, lport, rport);
}

UDPClientSocketUO::~UDPClientSocketUO()
{
	m_udpsock.close();
}

void UDPClientSocketUO::IniSynchroUDP_Client(std::string IP, int lport, int rport)
{
	//boost::asio::ip::udp::endpoint local_endpoint(boost::asio::ip::udp::udp::v4(),lport);
	//boost::system::error_code error = boost::asio::error::host_not_found;
	//m_udpsock.connect(local_endpoint,error);

	boost::asio::ip::udp::udp::resolver resolver(m_io_service);
	//boost::asio::ip::udp::udp::resolver::query query(boost::asio::ip::udp::udp::v4(), IP, boost::lexical_cast<std::string>(rport));
	boost::asio::ip::udp::udp::resolver::query query(IP, boost::lexical_cast<std::string>(rport));
	boost::asio::ip::udp::udp::resolver::iterator iter = resolver.resolve(query);

	m_remote_endpoint = *iter;

}

void UDPClientSocketUO::SynchroUDP_Send(const std::string &msg)
{
	try
	{
		m_udpsock.send_to(boost::asio::buffer(msg, msg.size()), m_remote_endpoint);
	}
	catch (const std::exception& e)
	{
		auto tmp = e.what();
	}
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

/////////////////////////////////////////UDP_Server//////////////////////////////
UDPServerSocketUO::UDPServerSocketUO(int lport) : m_udpsock(m_io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), lport))
{
	Start_Receive();
	m_io_service.run();
}

UDPServerSocketUO::~UDPServerSocketUO()
{
	m_udpsock.close();
}

void UDPServerSocketUO::Start_Receive()
{
	char buf[100] = { 0 };
	m_udpsock.async_receive_from(
		boost::asio::buffer(buf), m_remote_endpoint,
		boost::bind(&UDPServerSocketUO::Handle_Receive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	std::cout << "aasssssa" << std::endl;
}

void UDPServerSocketUO::Handle_Receive(const boost::system::error_code& error, std::size_t )
{
	if (!error || error == boost::asio::error::message_size)
	{
		std::cout << "received from<" << m_remote_endpoint.address().to_string() << ":" << m_remote_endpoint.port() << ">" << std::endl;
		Start_Receive();
	}
}
////////////////////////////TCP Client///////////////////////////////////////
TCPClientUO::TCPClientUO():m_socket(m_ios)
{
}

TCPClientUO::~TCPClientUO()
{
	m_socket.close();
}

void TCPClientUO::iniSynchroTCP_Client(std::string IP, int port)
{
	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(IP), port);
	try
	{
		m_socket.connect(endpoint);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TCPClientUO::SynchroTCP_Send(const std::string msg)
{
	try
	{
		m_socket.write_some(boost::asio::buffer(msg.data(), msg.size()));
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
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
/////////////////////////////////TCP Server///////////////////////////////
TCPServerUO::TCPServerUO() :m_acc(m_ios)//, m_sock(m_ios)
{
	m_breaded = false;
	//m_buffer.data()[0] = '\0';
	m_buffer = new char[2048];
	memset(m_buffer,0,2048);
}

TCPServerUO::~TCPServerUO()
{
	delete []m_buffer;
}

void TCPServerUO::runSynchroTCP_Server(int port)
{
	iniSynchroTCP_Server(port);
}

void TCPServerUO::iniSynchroTCP_Server(const int &port)
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

void TCPServerUO::client_session(const boost::shared_ptr<boost::asio::ip::tcp::socket> &sock)
{
	while (true)
	{
		char data[128] = { 0 };
		try
		{
			size_t len = sock->read_some(boost::asio::buffer(data, 128));
			if (len > 0)
			{
				std::cout << "form IP:" << sock->remote_endpoint().address() << " " << "port:" << sock->remote_endpoint().port() << std::endl;
				std::cout << "Data:" << '\t' << data << std::endl;
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

void TCPServerUO::runAsyncTCP_Server(int port)
{
	iniAsyncTCP_Server(port);
	start_accept();
	for (size_t i = 0; i < 2; i++)
	{
		boost::thread(boost::bind(&TCPServerUO::runthread,this));
	}
	runthread();
}

void TCPServerUO::iniAsyncTCP_Server(const int &port)
{
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port);
	//boost::shared_ptr<boost::asio::ip::tcp::socket> m_psock(new boost::asio::ip::tcp::socket(m_ios));
	//m_psock = boost::make_shared<boost::asio::ip::tcp::socket>(m_ios);
	m_acc.open(ep.protocol());
	m_acc.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
	m_acc.bind(ep);
	m_acc.listen();
}

void TCPServerUO::start_accept()
{
	share_ptr_sock clientsock(new boost::asio::ip::tcp::socket(m_ios));
	//boost::asio::ip::tcp::socket *clientsock = new boost::asio::ip::tcp::socket(m_ios);
	try
	{
		m_acc.async_accept(*clientsock, boost::bind(&TCPServerUO::handle_accept, this, clientsock, _1));
	}
	catch (const boost::system::system_error& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TCPServerUO::runthread()
{
	m_ios.run();
}

void TCPServerUO::handle_accept(share_ptr_sock &sock, const boost::system::error_code &err)
{
	if (err)
		return;
	{
		client_session2(sock);
	}
	start_accept();
}

void TCPServerUO::client_session2(share_ptr_sock &sock)
{
	try
	{
		std::cout << "form IP:" << sock->remote_endpoint().address() << " " << "port:" << sock->remote_endpoint().port() << std::endl;
		boost::asio::async_read(*sock, boost::asio::buffer(m_buffer, 2), boost::bind(&TCPServerUO::handle_read, this, sock, _1, _2));
		//sock->async_read_some(boost::asio::buffer(m_buffer,128), boost::bind(&TCPServerUO::handle_read, this, sock, _1, _2));
		//boost::asio::deadline_timer t(m_ios,boost::posix_time::seconds(10));
		//t.async_wait(boost::bind(&TCPServerUO::deadline_handler,this, sock, _1));
	}
	catch (const boost::system::system_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TCPServerUO::handle_read(share_ptr_sock &sock,const boost::system::error_code &err, const std::size_t &bytes_transferred)
{
	if (!err) 
	{
		if (bytes_transferred > 0)
		{
			std::cout << "Data:" << '\t' << m_buffer << std::endl;
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
Adaptor::Adaptor(MSGqueue<STRPACKET> *in):m_in(in)
{
	//m_thrd = boost::thread(boost::bind(&PacketUO::SubmitPacket, &PACKET, m_pSocket, m_cmd, m_allsubgrp));
	//m_thrd.interrupt();
}

Adaptor::~Adaptor()
{

}

void Adaptor::SendToSocket()
{
	while (true)
	{
		if (m_in->haspacket())
		{
			STRPACKET* tmp;
			while ((tmp = GetFromMQ(m_in)) != NULL)
			{
				////deal with packet SerializePacket(*tmp);
				//send
			}
		}
	}
}

void Adaptor::SendToMQ()
{
	while (true)
	{
		if (m_in->haspacket())
		{
			STRPACKET* tmp;
			while ((tmp = GetFromMQ(m_in)) != NULL)
			{
				//	dela with Packet PutToMQ(tmp)
			}
		}
		break;
	}
}

STRPACKET* Adaptor::GetFromMQ(MSGqueue<STRPACKET>* in)
{
	if (in->getsize())
		return in->getPacket();
	else
		return NULL;
}

std::string Adaptor::SerializePacket(const STRPACKET &packet)
{
	std::ostringstream os;
	boost::archive::binary_oarchive oa(os);
	oa << packet;
	return os.str();
}

STRPACKET Adaptor::UnSerializePacket(const std::string str)
{
	STRPACKET packet;
	std::istringstream is(str);
	boost::archive::binary_iarchive ia(is);
	ia >> packet;//从一个保存序列化数据的string里面反序列化，从而得到原来的对象。  
	return packet;
}

void Adaptor::PutToMQ(STRPACKET *packet)
{
	m_out->putPacket(*packet);
}