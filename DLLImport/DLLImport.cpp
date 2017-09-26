// DLLImport.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>  
#include <iostream>
#include "../DLL/DLLexport.h"
#pragma comment(lib, "DLL.lib")

// 在调用处添加如下代码  
//using pExport = Interface* (*)(void); // 定义指向导出函数的指针类型  
typedef Interface* (*pExport)(void);

int main()
{
	Interface *p = Export();
	p->ShowMsg();
	delete p;

	DLLClass *p2 = TCreatDLLClass();
	p2->show();
	delete p2;

	UOSupport aa;
	aa.ShowMsg();
	aa.CreatDLLClass()->show();

	HINSTANCE hDll = LoadLibrary("DLL.dll");// 加载DLL库文件，DLL名称和路径用自己的  
	if (hDll == NULL)
	{
		std::cout << "load dll fail \n";
		return -1;
	}
	pExport Get = (pExport)GetProcAddress(hDll, "Export");// 将指针指向函数首地址  
	if (Get == NULL)
	{
		std::cout << "load address fail \n";
		return -1;
	}

	Interface *t = Get();// 调用导出函数获得抽象类指针  
	t->ShowMsg();
	delete t; 
	FreeLibrary(hDll); //释放库句柄  
	system("pause");
    return 0;
}

