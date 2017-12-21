#pragma once
#include <iostream>

class fun;

class BASE
{
public:
	fun *m_pfun;
	virtual void base1() {};
};

class A :public BASE
{
public:
	void base1();
};