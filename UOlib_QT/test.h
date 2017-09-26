#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <qdialog.h>
#include "ui_test.h"

class test : public QDialog
{
	Q_OBJECT

public:
	test(QWidget *parent = 0);
	~test();
	void testbt(std::string str);
private:
	Ui::test ui;
};

#endif // TEST_H
