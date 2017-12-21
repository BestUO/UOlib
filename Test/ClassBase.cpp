#include "ClassBase.h"
#include "ClassFun.h"

void A::base1()
{
	if (!m_pfun)
		m_pfun = new fun();
	m_pfun->fun2();
}