#include "test.h"

test::test(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

test::~test()
{

}

void test::testbt(std::string str)
{
	ui.label->setText(str.c_str());
}