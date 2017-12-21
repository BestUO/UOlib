// MemLeakCheck.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
//FUN A better auto show the locate
#include "vld.h"
#pragma comment(lib, "vld.lib")
//FUN B need define new  new(_CLIENT_BLOCK, __FILE__, __LINE__) in every .cpp to show the locate
//#include <stdlib.h>  
//#include <crtdbg.h>  
//#define new  new(_CLIENT_BLOCK, __FILE__, __LINE__)

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::cout << "hahahah" << std::endl;
	char* tmp = new char[10];
	memset(tmp, 0, 10);
    return 0;
}