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
#include <time.h>
#include "Globle.h"
#include <mutex>

#define BUFSIZE 1460

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

/////////////////////////////////////////////Message Queue///////////////////////////////////////////////
template <typename T>
class MSGqueue
{
	typedef T struct_type;
public:
	MSGqueue() { memset(&m_Packet, 0, sizeof(struct_type)); m_nSingals = 0; }
	~MSGqueue() {}

	int getsize()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_MSGlist.size();
	}
	struct_type getPacket()
	{
		//WaitSignal();
		std::unique_lock<std::mutex> lock(m_mutex);
		if (!m_nSingals)
			m_cv.wait(lock);
		m_nSingals--;
		if (m_MSGlist.size())
		{
			m_Packet = m_MSGlist.front();
			m_MSGlist.pop_front();
			return m_Packet;
		}
		else
			return nullptr;
	}
	void putPacket(const struct_type &packet)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_nSingals++;
		m_MSGlist.push_back(packet);
		m_cv.notify_one();
	}

private:
	std::list<struct_type> m_MSGlist;
	struct_type m_Packet;
	std::mutex m_mutex;
	std::condition_variable m_cv;
	uint16_t m_nSingals;

	bool WaitSignal()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		if (!m_nSingals)
			m_cv.wait(lock);
		m_nSingals--;
		return true;
	}
};

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
};

class SocketClientInterface
{
public:
	virtual ~SocketClientInterface() {};
	virtual void send(std::string s) = 0;
	virtual std::string receive() = 0;
	virtual void disconnect() = 0;
};

class UDPClientSocketUO : public SocketClientInterface
{
public:
	UDPClientSocketUO(std::string IP, int rport);
	~UDPClientSocketUO();
	void send(std::string s)
	{
		SynchroUDP_Send(s);
		//std::cout << SynchroUDP_Receive();
	}
	std::string receive() { return ""; }
	void disconnect() { m_udpsock.close(); }
private:
	boost::asio::io_service m_io_service;
	boost::asio::ip::udp::endpoint m_remote_endpoint;
	boost::asio::ip::udp::socket m_udpsock;

	bool IniSocket(std::string IP, int rport);
	bool SynchroUDP_Send(const std::string &msg);
	std::string SynchroUDP_Receive();
};

class TCPClientUO :public SocketClientInterface
{
public:
	TCPClientUO(std::string IP, int port);
	~TCPClientUO();
	void send(std::string s)
	{
		SynchroTCP_Send(s);
		//std::cout << SynchroTCP_Recv();
	}
	std::string receive() { return ""; }
	void disconnect() { m_socket.close(); }
private:
	boost::asio::io_service m_ios;
	boost::asio::ip::tcp::socket m_socket;

	bool iniSynchroTCP_Client(std::string IP, int port);
	bool SynchroTCP_Send(const std::string msg);

	std::string SynchroTCP_Recv();
};

class SocketServerInterface
{
public:
	virtual ~SocketServerInterface() {};
	virtual void runserver(int port) = 0;
	virtual void stopserver() = 0;
	bool setMQdst(std::shared_ptr<MSGqueue<std::string>> pMQ) 
	{
		if (pMQ)
		{
			m_pMQ = pMQ;
			return true;
		}
		return false;
	}
protected:
	std::shared_ptr<MSGqueue<std::string>> m_pMQ;
};

//template <class TYPE> class MSGqueue;
class UDPServerSocketUO : public SocketServerInterface
{
public:
	UDPServerSocketUO();
	~UDPServerSocketUO();

	void runserver(int port);
	void stopserver() { m_io_service.stop(); }

private:
	void Start_Receive();
	void Handle_Receive(const boost::system::error_code& error, std::size_t bytes_transferred);
	std::string MakePacket(char* data, int len);
private:
	std::string m_str;
	char m_buf[BUFSIZE];
	boost::asio::ip::udp::endpoint m_remote_endpoint;
	boost::asio::io_service m_io_service;
	boost::asio::ip::udp::socket m_udpsock;
};

class TCPServerUO : public SocketServerInterface
{
	typedef std::shared_ptr<boost::asio::ip::tcp::socket> share_ptr_sock;
public:
	TCPServerUO();
	~TCPServerUO();

	void runserver(int port);
	void stopserver() { m_ios.stop(); }

private:
	void runSynchroTCP_Server(const int &port);
	void client_session(const boost::shared_ptr<boost::asio::ip::tcp::socket> sock);
	std::string MakePacket(char* data, int len);

	void runAsyncTCP_Server(const int &port);
	void iniAsyncTCP_Server(const int &port);
	void start_accept();
	void handle_accept(share_ptr_sock sock,const boost::system::error_code &err);
	void client_session2(share_ptr_sock sock);
	void handle_read(share_ptr_sock sock, const boost::system::error_code &err, const std::size_t &bytes_transferred);

private:
	boost::asio::io_service m_ios;
	boost::asio::ip::tcp::acceptor m_acc;
	bool m_breaded;
	std::string m_str;
	char m_buf[BUFSIZE];
};

/////////////////////////////////////////////Adaptor Class//////////////////////////////////////////////
//class Adaptor
//{
//public:
//	Adaptor(MSGqueue<STRPACKET> *in);
//	~Adaptor();
//	/////////////////////MQ To Socket
//	void SendToSocket();
//	/////////////////////MQ TO MQ
//	void SendToMQ();
//
//private:
//	std::string SerializePacket(const STRPACKET &packet);
//	STRPACKET UnSerializePacket(const std::string str);
//	STRPACKET* GetFromMQ(MSGqueue<STRPACKET>* in);
//	void PutToMQ(STRPACKET *packet);
//
//private:
//	MSGqueue<STRPACKET> *m_in;
//	MSGqueue<STRPACKET> *m_out;
//};