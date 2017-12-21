#pragma once
#include<string>
#include <iostream>   

#ifdef INTERFACE_EXPORTS  
#define INTERFACE_API __declspec(dllexport)  
#else  
#define INTERFACE_API __declspec(dllimport)  
#endif  
/////////////////////////////dll 导出虚函数接口
class Interface
{
public:
	virtual void ShowMsg() = 0; // 将调用方需要调用的成员函数声明成纯虚函数  
	virtual ~Interface() {};// 抽象类的虚析构函数  
};
extern "C" INTERFACE_API Interface* Export(void);

/////////////////////////////////用函数导出类指针
class DLLClass
{
public:
	void show() { std::cout << "DLLclass" << std::endl; }
};
extern "C" INTERFACE_API DLLClass* TCreatDLLClass(void);

//////////////////////////////////导出一个类，但是符号名是乱的,不建议这么做
class INTERFACE_API UOSupport
{
public:
	DLLClass* CreatDLLClass();
	void ShowMsg();
};

#undef INTERFACE_API

