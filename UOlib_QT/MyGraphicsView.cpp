#include "MyGraphicsView.h"
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QWheelEvent>


MyGraphicsView::MyGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{

}

MyGraphicsView::MyGraphicsView(QGraphicsScene *scene, QWidget *parent)
	: QGraphicsView(scene, parent)
{
}

MyGraphicsView::~MyGraphicsView()
{
}

bool MyGraphicsView::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::Wheel)
	{
		QMouseEvent *MouseEvent = (QMouseEvent *)(event);
		if(itemAt(MouseEvent->pos()))
		{
			event->ignore();
			return true;
		}
		else
		{
			event->accept();
			return false;
		}
		//this->mapToScene(x,y);
	}
	//if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonRelease)
	//{
	//	event->accept();
	//	return false;
	//}
	return QGraphicsView::eventFilter(obj, event);
}