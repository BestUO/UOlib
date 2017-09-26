#define INTERFACE_EXPORTS
#include "DLLexport.h"
#include "testDLL.h"

Interface* Export(void)
{
	return (Interface*)new testDLL();
}

DLLClass* TCreatDLLClass()
{
	return new DLLClass();
}

DLLClass* UOSupport::CreatDLLClass()
{
	return new DLLClass();
}

void UOSupport::ShowMsg()
{
	std::cout << "haha" << std::endl;
}