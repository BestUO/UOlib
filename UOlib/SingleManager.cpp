#include "SingleManager.h"


bool CDealData::setMQdst(std::shared_ptr<MSGqueue<std::string>> pMQ)
{
	if (pMQ)
	{
		m_pMQdst = pMQ;
		return true;
	}
	return false;
}

bool CDealData::setMQsrc(std::shared_ptr<MSGqueue<std::string>> pMQ)
{
	if (pMQ)
	{
		m_pMQsrc = pMQ;
		return true;
	}
	return false;
}

void CDealData::DealDataAndSend()
{
	while (m_pMQsrc && !m_stop)
	{
		std::string str;
		m_pMQsrc->getPacket(str);
		str = DealData(str);
		SendToMQ(str);
	}
}

std::string CDealData::DealData(const std::string& s)
{
	return s;
}

bool AdaptorClient::setMQsrc(std::shared_ptr<MSGqueue<std::string>> pMQ)
{
	if (pMQ)
	{
		m_pMQ = pMQ;
		return true;
	}
	return false;
}
void AdaptorClient::Connect(SocketType type, std::string IP, int port)
{
	switch (type)
	{
	case ClientTCP:
		m_psock = new TCPClientUO(IP, port);
		break;
	case ClientUDP:
		m_psock = new UDPClientSocketUO(IP, port);
		break;
	}
}
void AdaptorClient::Send()
{
	while (m_pMQ && !m_stop)
	{
		std::string str;
		m_pMQ->getPacket(str);
		m_psock->send(str);
	}
	return;
}

void AdaptorServer::runServer(SocketType type, int port)
{
	switch (type)
	{
	case ServerTCP:
		m_psockServer = new TCPServerUO();
		m_psockServer->runserver(port);
		break;
	case ServerUDP:
		m_psockServer = new UDPServerSocketUO();
		m_psockServer->runserver(port);
		break;
	}
}

SingleManager::SingleManager()
{
}

SingleManager::~SingleManager()
{
	if (m_type == ClientTCP || m_type == ClientUDP)
	{
		m_SockClient.setstop(true);
		m_Cfun.setstop(true);
		m_pMQsrc->putPacket("EXIT");
		m_dealthread.join();
		m_sendthread.join();
	}
	if (m_type == ServerTCP || m_type == ServerUDP)
	{
		m_SockServer.stopServer();
		m_Cfun.setstop(true);
		m_pMQdst->putPacket("EXIT");
		m_dealthread.join();
	}
}

void SingleManager::iniClientStruct()
{
	CreateClient(ClientTCP, "127.0.0.1", 1234);
	m_type = ClientTCP;
}

void SingleManager::iniServerStruct()
{
	CreateServer(ServerUDP,9876);
	m_type = ServerUDP;
}

void SingleManager::CreateServer(SocketType type, int port)
{
	m_pMQdst = std::shared_ptr<MSGqueue<std::string>>(new MSGqueue<std::string>);
	m_pMQsrc = std::shared_ptr<MSGqueue<std::string>>(new MSGqueue<std::string>);
	m_SockServer.runServer(type, port);
	m_SockServer.setMQdst(m_pMQdst);

	m_Cfun.setMQsrc(m_pMQdst);
	m_Cfun.setMQdst(m_pMQsrc);
	m_dealthread = std::thread(&CDealData::DealDataAndSend, &m_Cfun);		//处理线程
}

void SingleManager::CreateClient(SocketType type,std::string IP,int port)
{
	m_pMQsrc = std::shared_ptr<MSGqueue<std::string>>(new MSGqueue<std::string>);
	m_pMQdst = std::shared_ptr<MSGqueue<std::string>>(new MSGqueue<std::string>);

	m_Cfun.setMQsrc(m_pMQsrc);
	m_Cfun.setMQdst(m_pMQdst);
	m_SockClient.setMQsrc(m_pMQdst);
	m_SockClient.Connect(type, IP, port);

	m_dealthread = std::thread(&CDealData::DealDataAndSend, &m_Cfun);		//处理线程
	m_sendthread = std::thread(&AdaptorClient::Send, &m_SockClient);			//发送线程
}

void SingleManager::send(std::string s)
{
	if (m_type == ClientTCP || m_type == ClientUDP)
		m_pMQsrc->putPacket(s);
}

void SingleManager::disconnect()
{
	if (m_type == ClientTCP || m_type == ClientUDP)
		m_SockClient.disconnect();
}

void SingleManager::stopserver()
{
	if (m_type == ServerTCP || m_type == ServerUDP)
		m_SockServer.stopServer();
}