#pragma once
#include <iostream>
#include "ClassBase.h"

class fun
{
private:
	BASE* ttt;
public:
	void fun1()
	{
		std::cout << "fun1";
		ttt = new A();
		ttt->base1();
	}
	void fun2() { std::cout << "fun2"; }
};