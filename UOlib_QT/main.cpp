#include "UOlib_qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	UOlib_QT w;
	w.show();
	return a.exec();
}
