#pragma once

#include"UOSupport.h"
#include"Globle.h"
#include<map>
#include <thread>

class CDealData
{
public:
	CDealData() { m_stop = false; }
	void setstop(bool stop) { m_stop = stop; }
	bool setMQdst(std::shared_ptr<MSGqueue<std::string>> pMQ);
	bool setMQsrc(std::shared_ptr<MSGqueue<std::string>> pMQ);
	void DealDataAndSend();

private:
	std::shared_ptr<MSGqueue<std::string>> m_pMQdst;
	std::shared_ptr<MSGqueue<std::string>> m_pMQsrc;
	bool m_stop;

	std::string DealData(const std::string& s);
	void SendToMQ(std::string s) { m_pMQdst->putPacket(s); }
};

enum SocketType{ ServerTCP, ServerUDP, ClientTCP, ClientUDP };
class AdaptorClient
{
public:
	AdaptorClient() { m_stop = false; }
	~AdaptorClient() { delete m_psock; }
	bool setMQsrc(std::shared_ptr<MSGqueue<std::string>> pMQ);
	void Connect(SocketType type, std::string IP, int port);
	void Send();
	void setstop(bool stop) { m_stop = stop; }
	void disconnect() { m_psock->disconnect(); }

private:
	std::shared_ptr<MSGqueue<std::string>>	m_pMQ;
	SocketClientInterface*					m_psock;
	bool m_stop;
};

class AdaptorServer
{
public:
	AdaptorServer() {  }
	~AdaptorServer() { delete m_psockServer; }
	void setMQdst(std::shared_ptr<MSGqueue<std::string>> pMQ){ m_psockServer->setMQdst(pMQ); }
	void runServer(SocketType type, int port);
	void stopServer() { m_psockServer->stopserver(); }
private:
	SocketServerInterface*					m_psockServer;
};

#define MANAGER		Singleton<SingleManager>::GetInstance()
class SingleManager
{
private:
	SingleManager();
	~SingleManager();
	friend class Singleton<SingleManager>;

public:
	void iniClientStruct();
	void send(std::string s);
	void disconnect();
	void iniServerStruct();
	void stopserver();

private:
	//std::map<std::string, std::shared_ptr<MSGqueue<std::string>>> m_map;
	std::shared_ptr<MSGqueue<std::string>> m_pMQsrc;
	std::shared_ptr<MSGqueue<std::string>> m_pMQdst;
	SocketType	m_type;
	CDealData m_Cfun;
	std::thread m_dealthread;

	//ClientStruct
	AdaptorClient m_SockClient;
	std::thread m_sendthread;
	void CreateClient(SocketType type, std::string IP, int port);
	
	//ServerStruct
	AdaptorServer m_SockServer;
	void CreateServer(SocketType type, int port);
};

