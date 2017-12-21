// UOlib.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "UOSupport.h"
#include <algorithm>
#include"SingleManager.h"
#include "wav.h"
#include <io.h>
int main()
{
	//uint16_t a = 32778;
	//char b[2] = { 0 };
	//b[0] = a & 0xff;
	//b[1] = (a >> 8 ) & 0xff;
	//UOSupport::UOFile aa;
	//aa.WriteFile("UO.data", b, 2);

	//char t[10240] = { 0 };
	//int len = aa.ReadFile("UO.data", t);
	//uint16_t *c = (uint16_t*)t;

	//char dir[200];
	//cout << "Enter a directory: ";
	//cin.getline(dir, 200);
	//UOSupport::UOFile aa;
	//aa.listFiles(dir);

	//UDPClientSocketUO tt("127.0.0.1",6000);
	//tt.SynchroUDP_Send("hhaha");
	//tt.SynchroUDP_Receive();

	//UDPServerSocketUO aa(5000);

	//TCPClientUO aa;
	//aa.iniSynchroTCP_Client("127.0.0.1", 1234);
	//aa.SynchroTCP_Send("aaaa");

	//TCPServerUO aa;
	//aa.runSynchroTCP_Server(6000);
	//aa.runAsyncTCP_Server(6000);

	//double aa = UOTemplate<double>::ConvertFromString("111.222222222");
	//std::string str = UOTemplate<double>::ConvertToString(12211.222);

	//#define MANAGER		Singleton<SingletonManager>::GetInstance()
	//#define SUPPORT		Singleton<SingletonManager>::GetInstance().GetSupportInstance()

	//class SingletonManager
	//{
	//protected:
	//	SingletonManager() {};
	//	~SingletonManager() {};
	//	friend class Singleton<SingletonManager>;
	//public:
	//	void do_something() { std::cout << "hello" << std::endl; };
	//	UOSupport::UOFile& GetSupportInstance() { return m_UOFile; };

	//private:
	//	UOSupport::UOFile m_UOFile;
	//};

	//SUPPORT.test();
	//MANAGER.do_something();

	//MSGqueue<STRPACKET> tmp;
	//Adaptor adaptor(&tmp);
	//
	//boost::thread t1(boost::bind(&Adaptor::SendToMQ, &adaptor));
	//Sleep(2000);
	//tmp.m_cv.notify_one();
	//t1.join();

	//UOObserver ob1("111");
	//UOObserver ob2("222");
	//UOSubject sb;
	//sb.connect(boost::bind(&UOObserver::test, ob1));
	//sb.connect(boost::bind(&UOObserver::test, ob2));
	//sb.EMITsignal();
	 
	//MANAGER.iniClientStruct();
	//system("pause");
	//MANAGER.disconnect();
	//MANAGER.iniServerStruct();
	//system("pause");
	//MANAGER.stopserver();
	system("md test");
	return 0;
}

