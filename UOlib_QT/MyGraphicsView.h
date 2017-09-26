#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	MyGraphicsView(QWidget *parent = Q_NULLPTR);
	MyGraphicsView(QGraphicsScene *scene, QWidget *parent = Q_NULLPTR);
	~MyGraphicsView();

protected:
	bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MYGRAPHICSVIEW_H
