#include "testDLL.h"
#include <iostream>  

testDLL::testDLL()
{
	s = "hello form dll";
}

testDLL::~testDLL()
{
	std::cout << "destroy";
}

void testDLL::ShowMsg()
{
	std::cout << s << std::endl;
}