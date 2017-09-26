#include "UOlib_qt.h"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Customitem.h"
#include "MyPlot.h"
#include "test.h"

UOlib_QT::UOlib_QT(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	inishow();
	//connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(testbt()));
}

UOlib_QT::~UOlib_QT()
{
	qDeleteAll(m_vspPlot);
}

void UOlib_QT::testbt()
{
	
}

void UOlib_QT::inishow()
{
	int gridSize = 8;
	for (int x = 0; x < gridSize; ++x)
	{
		for (int y = 0; y < gridSize; ++y)
		{
			MyPlot *aa = new MyPlot();
			aa->setMinimumSize(400,250);
			m_vspPlot.push_back(aa);
			Customitem *item = new Customitem(0, Qt::Widget);
			item->setWidget(aa);
			QRectF rect = item->boundingRect();
			item->setPos(y * rect.width() * 1.05, x * rect.height() * 1.05);
			//item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
			//item->setCacheMode(QGraphicsItem::NoCache);
			scene.addItem(item);
		}
	}
	//scene.setSceneRect(ui.graphicsView->rect());
	//scene.addRect(ui.graphicsView->rect(), QPen(Qt::red));//把场景范围直观显示出来，只为了方便理解
	scene.setStickyFocus(true);
	ui.graphicsView->setScene(&scene);
	ui.graphicsView->scale(0.2, 0.2);
	ui.graphicsView->setRenderHints(ui.graphicsView->renderHints() | QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	ui.graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	//ui.graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//ui.graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.graphicsView->show();
}