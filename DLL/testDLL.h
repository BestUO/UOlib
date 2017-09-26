#pragma once
#include "DLLexport.h"  
#include <string> 

class testDLL :public Interface
{
public:
	testDLL();
	virtual ~testDLL();
	virtual void ShowMsg(void);
private:
	std::string s;
};