#ifndef UOLIB_QT_H
#define UOLIB_QT_H

#include <QtWidgets/QWidget>
#include "ui_UOlib_qt.h"
#include "MyPlot.h"
#include "test.h"

class UOlib_QT : public QWidget
{
	Q_OBJECT

public:
	UOlib_QT(QWidget *parent = 0);
	~UOlib_QT();

public:
	void inishow();
private:
	Ui::UOlib_QTClass ui;
	QGraphicsScene scene;
	QVector<MyPlot*> m_vspPlot;
	/*MyPlot *spPlot;
	QWidget tmpw;*/

private slots:
	void testbt();
};

#endif // UOLIB_QT_H
