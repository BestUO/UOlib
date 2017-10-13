#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0603
#endif

#include <string>
#include <iostream>
#include <fstream>  
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/signals2.hpp>
#include "Globle.h"

class UOSupport
{
public:
	class UOFile
	{
	public:
		UOFile();
		~UOFile();
		void WriteFile(std::string Path, char *data,int len);
		int ReadFile(std::string Path, char *data);
	};
	class UOsort
	{
		//make_heap
		//push_heap
		//pop_heap
		//sort_heap/std::partial_sort/std::sort	
	};
};

class UDPClientSocketUO
{
public:
	UDPClientSocketUO(std::string IP, int rport);
	UDPClientSocketUO(std::string IP, int lport, int rport);
	~UDPClientSocketUO();

public:
	void SynchroUDP_Send(const std::string &msg);
	std::string SynchroUDP_Receive();

private:
	void IniSynchroUDP_Client(std::string IP, int lport, int rport);

private:
	boost::asio::io_service m_io_service;

	boost::asio::ip::udp::endpoint m_remote_endpoint;
	boost::asio::ip::udp::socket m_udpsock;
};

class UDPServerSocketUO
{
public:
	UDPServerSocketUO(int lport);
	~UDPServerSocketUO();

private:
	void Start_Receive();
	void Handle_Receive(const boost::system::error_code& error, std::size_t);

private:
	boost::asio::ip::udp::endpoint m_remote_endpoint;
	boost::asio::io_service m_io_service;
	boost::asio::ip::udp::socket m_udpsock;
};

class TCPClientUO
{
public:
	TCPClientUO();
	~TCPClientUO(); 
public:
	void iniSynchroTCP_Client(std::string IP, int port);
	void SynchroTCP_Send(const std::string msg);

	std::string SynchroTCP_Recv();
private:
	boost::asio::io_service m_ios;
	boost::asio::ip::tcp::socket m_socket;
};

class TCPServerUO
{
	typedef boost::shared_ptr<boost::asio::ip::tcp::socket> share_ptr_sock;
public:
	TCPServerUO();
	~TCPServerUO();

public:
	void runSynchroTCP_Server(int port);
	void runAsyncTCP_Server(int port);

private:
	void iniSynchroTCP_Server(const int &port);
	void client_session(const boost::shared_ptr<boost::asio::ip::tcp::socket> &sock);

	void iniAsyncTCP_Server(const int &port);
	void start_accept();
	void runthread();
	void handle_accept(share_ptr_sock &sock,const boost::system::error_code &err);
	void client_session2(share_ptr_sock &sock);
	void handle_read(share_ptr_sock &sock, const boost::system::error_code &err, const std::size_t &bytes_transferred);
	//void deadline_handler(share_ptr_sock &sock,const boost::system::error_code &err);

	//void handle_accept(boost::asio::ip::tcp::socket *sock, const boost::system::error_code &err);
	//void client_session2(boost::asio::ip::tcp::socket *sock);
	//void handle_read(boost::asio::ip::tcp::socket *sock, const boost::system::error_code &err, const std::size_t &bytes_transferred);
	//void deadline_handler(boost::asio::ip::tcp::socket *sock, const boost::system::error_code &err);

private:
	
	boost::asio::io_service m_ios;
	//::asio::ip::tcp::socket m_sock;
	//boost::shared_ptr<boost::asio::ip::tcp::socket> m_psock;
	boost::asio::ip::tcp::acceptor m_acc;
	bool m_breaded;
	char *m_buffer;
};

template <class T>
class UOTemplate
{
public:
	////also work
	//static T ConvertFromString(const std::string &s)
	//{
	//	T value;
	//	std::stringstream ss(s);
	//	ss >> value;
	//	return value;
	//}
	//static std::string ConvertToString(const T &value)
	//{
	//	std::stringstream ss;
	//	ss << value;
	//	return ss.str();
	//}
	static T ConvertFromString(const std::string &s)
	{
		return boost::lexical_cast<T>(s);
	}
	static std::string ConvertToString(const T &value)
	{
		return boost::lexical_cast<std::string>(s);
	}
};

/////////////////////////////////////////////Singleton Class//////////////////////////////////////////////
template <typename T>
class Singleton
{
	struct object_creator
	{
		object_creator() { Singleton<T>::GetInstance(); }
		inline void do_nothing()const {}
	};
	static object_creator create_object;

public:
	typedef T object_type;
	static object_type& GetInstance()
	{
		static object_type obj;
		//据说这个do_nothing是确保create_object构造函数被调用
		//这跟模板的编译有关
		create_object.do_nothing();
		return obj;
	}
};
template <typename T> typename Singleton<T>::object_creator Singleton<T>::create_object;

//class QMManager
//{
//protected:
//	QMManager();
//	~QMManager() {};
//	friend class Singleton<QMManager>;
//public:
//	void do_something() {};
//};
//
//int main()
//{
//	Singleton<QMManager>::instance()->do_something();
//	return 0;
//}

/////////////////////////////////////////////Message Queue///////////////////////////////////////////////
template <typename T>
class MSGqueue
{
	typedef T struct_type;
public:
	MSGqueue() { memset(&m_Packet, 0, sizeof(struct_type)); }
	~MSGqueue(){}

	int getsize()
	{
		boost::unique_lock<boost::shared_mutex> lock(m_mutex);
		return m_MSGlist.size();
	}
	struct_type* getPacket()
	{
		boost::unique_lock<boost::shared_mutex> lock(m_mutex);
		m_Packet = m_MSGlist.back();
		m_MSGlist.pop_back();
		return &m_Packet;
	}
	void putPacket(const struct_type &packet)
	{
		boost::unique_lock<boost::shared_mutex> lock(m_mutex);
		m_MSGlist.push_front(packet);
		m_cv.notify_one();
	}
	bool haspacket()
	{
		boost::unique_lock<boost::mutex> lck(m_mtSig);
		m_cv.wait(lck);
		return true;
	}
private:
	std::list<struct_type> m_MSGlist;
	struct_type m_Packet;
	boost::shared_mutex m_mutex;
	boost::mutex m_mtSig;
public:
	boost::condition_variable m_cv;
};

/////////////////////////////////////////////Adaptor Class//////////////////////////////////////////////
class Adaptor
{
public:
	Adaptor(MSGqueue<STRPACKET> *in);
	~Adaptor();
	/////////////////////MQ To Socket
	void SendToSocket();
	/////////////////////MQ TO MQ
	void SendToMQ();

private:
	std::string SerializePacket(const STRPACKET &packet);
	STRPACKET UnSerializePacket(const std::string str);
	STRPACKET* GetFromMQ(MSGqueue<STRPACKET>* in);
	void PutToMQ(STRPACKET *packet);

private:
	MSGqueue<STRPACKET> *m_in;
	MSGqueue<STRPACKET> *m_out;
};

///////////////////////////////////////subject better use Singleton class////////////////////////////////
class UOSubject
{
	typedef boost::signals2::signal<void()> signal_t;
	typedef signal_t::slot_type slot_t;
public:
	UOSubject() {}
	~UOSubject() {}

	boost::signals2::connection connect(const slot_t &s) { return m_signal.connect(s); }
	//boost::signals2::connection connect(const boost::function<void()> &s) { return m_signal.connect(s); }
	void EMITsignal() { m_signal(); }
private:
	signal_t m_signal;
};
///////////////////////////////////////////////////Observer//////////////////////////////////////////////
class UOObserver
{
public:
	UOObserver(std::string name):m_name(name) {}
	UOObserver() {}

	void test() { std::cout << m_name.c_str() << std::endl; }
private:
	std::string m_name;
};