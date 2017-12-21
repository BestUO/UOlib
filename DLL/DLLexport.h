#pragma once
#include<string>
#include <iostream>   

#ifdef INTERFACE_EXPORTS  
#define INTERFACE_API __declspec(dllexport)  
#else  
#define INTERFACE_API __declspec(dllimport)  
#endif  
/////////////////////////////dll �����麯���ӿ�
class Interface
{
public:
	virtual void ShowMsg() = 0; // �����÷���Ҫ���õĳ�Ա���������ɴ��麯��  
	virtual ~Interface() {};// �����������������  
};
extern "C" INTERFACE_API Interface* Export(void);

/////////////////////////////////�ú���������ָ��
class DLLClass
{
public:
	void show() { std::cout << "DLLclass" << std::endl; }
};
extern "C" INTERFACE_API DLLClass* TCreatDLLClass(void);

//////////////////////////////////����һ���࣬���Ƿ��������ҵ�,��������ô��
class INTERFACE_API UOSupport
{
public:
	DLLClass* CreatDLLClass();
	void ShowMsg();
};

#undef INTERFACE_API

