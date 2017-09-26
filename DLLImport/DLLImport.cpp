// DLLImport.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>  
#include <iostream>
#include "../DLL/DLLexport.h"
#pragma comment(lib, "DLL.lib")

// �ڵ��ô�������´���  
//using pExport = Interface* (*)(void); // ����ָ�򵼳�������ָ������  
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

	HINSTANCE hDll = LoadLibrary("DLL.dll");// ����DLL���ļ���DLL���ƺ�·�����Լ���  
	if (hDll == NULL)
	{
		std::cout << "load dll fail \n";
		return -1;
	}
	pExport Get = (pExport)GetProcAddress(hDll, "Export");// ��ָ��ָ�����׵�ַ  
	if (Get == NULL)
	{
		std::cout << "load address fail \n";
		return -1;
	}

	Interface *t = Get();// ���õ���������ó�����ָ��  
	t->ShowMsg();
	delete t; 
	FreeLibrary(hDll); //�ͷſ���  
	system("pause");
    return 0;
}

