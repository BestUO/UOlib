#include "MyPlot.h"
#include "ToolFunc.h"
#include "CircularBuffer.h"

//#include <QPointF>

#include <qwt_plot_canvas.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_layout.h>
#include <qwt_scale_widget.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_symbol.h>
#include <qwt_plot_marker.h>

#include <QWheelEvent>
//#include <qwt_math.h>
//#include <math.h>


class MyZoomer : public QwtPlotZoomer
{
public:
	MyZoomer( QWidget *canvas )
		:	QwtPlotZoomer( canvas )
	{
		setTrackerMode( AlwaysOn );
	}

	virtual QwtText trackerTextF( const QPointF &pos ) const
	{
		QColor bg( Qt::white );
		bg.setAlpha( 200 );

		QString str = "[" + QString::number(pos.x(),'f',6) + "," + QString::number(pos.y(),'f',1) + "]";

		//QwtText text = QwtPlotZoomer::trackerTextF( pos );

		QwtText text(str);
		text.setBackgroundBrush( QBrush( bg ) );
		return text;
	}
};

class ArrowSymbol : public QwtSymbol
{
public:
	ArrowSymbol()
	{
		QPen pen( Qt::black, 0 );
		pen.setJoinStyle( Qt::MiterJoin );

		setPen( pen );
		setBrush( Qt::red );

		QPainterPath path;
		path.moveTo( 0, 8 );
		path.lineTo( 0, 5 );
		path.lineTo( -3, 5 );
		path.lineTo( 0, 0 );
		path.lineTo( 3, 5 );
		path.lineTo( 0, 5 );

		QTransform transform;
		transform.rotate( -30.0 );
		path = transform.map( path );

		setPath( path );
		setPinPoint( QPointF( 0, 0 ) );

		setSize( 10, 14 );
	}
};

MyPlot::MyPlot( QWidget *parent )
	:	QwtPlot( parent )
{
	// canvas
	QwtPlotCanvas * canvas0 = new QwtPlotCanvas();
	canvas0->setLineWidth( 1 );
	canvas0->setFrameStyle( QFrame::Box | QFrame::Plain );
	canvas0->setBorderRadius( 15 );

	QPalette canvasPalette( Qt::white );
	canvasPalette.setColor( QPalette::Background, QColor( 29, 100, 141 ) );
	canvas0->setPalette( canvasPalette );

	//setCanvasBackground( QColor( 29, 100, 141 ) ); // nice blue

	setCanvas( canvas0 );

    //setTitle( "Testing Refresh Rates" );

	setFrameStyle( QFrame::NoFrame );
	setLineWidth( 0 );

	plotLayout()->setAlignCanvasToScales( true );

	d_grid = new QwtPlotGrid;
	d_grid->setMajorPen( Qt::gray, 0, Qt::DotLine );
	d_grid->attach( this );

	d_curve = new QwtPlotCurve();
	d_curve->setPen( Qt::green );
	d_curve->setData( new CircularBuffer() );
	d_curve->attach( this );

	QFont f("宋体", 10);
	setAxisFont(QwtPlot::xBottom, f);
	setAxisFont(QwtPlot::yLeft, f);

	setAxisTitle( QwtPlot::xBottom, ZN_STR("频率(MHz)"));
	setAxisScale( QwtPlot::xBottom, 500, 800 );

	setAxisTitle( QwtPlot::yLeft, ZN_STR("电平(dBuV)"));
	setAxisScale( QwtPlot::yLeft, -30, 150 );

	//setCanvasBackground( QColor( 29, 100, 141 ) ); // nice blue

	setAutoReplot( false );

	d_cfreq = 0;
	d_bw = 0;

	/*QwtPlotZoomer* zoomer = new MyZoomer( canvas() );
	zoomer->setMousePattern( QwtEventPattern::MouseSelect2,Qt::RightButton, Qt::ControlModifier );
	zoomer->setMousePattern( QwtEventPattern::MouseSelect3,Qt::RightButton );
	
	const QColor c( Qt::darkBlue );
	zoomer->setRubberBandPen( c );
	zoomer->setTrackerPen( c );*/

	/*QwtPlotPanner *panner = new QwtPlotPanner( canvas() );
	panner->setAxisEnabled( QwtPlot::yRight, false );
	panner->setMouseButton( Qt::MidButton );*/

	( void ) new QwtPlotPanner( canvas() );
	( void ) new QwtPlotMagnifier( canvas() );

	const QFontMetrics fm( axisWidget( QwtPlot::yLeft )->font() );
	QwtScaleDraw *sd = axisScaleDraw( QwtPlot::yLeft );
	sd->setMinimumExtent( fm.width( "100.00" ) );

	d_maxMarker = new QwtPlotMarker( ZN_STR("最大值") );
	d_maxMarker->setRenderHint( QwtPlotItem::RenderAntialiased, true );
	d_maxMarker->setItemAttribute( QwtPlotItem::Legend, true );
	d_maxMarker->setSymbol( new ArrowSymbol() );
	d_maxMarker->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
	d_maxMarker->attach( this );

	//inivcurve();
}

MyPlot::~MyPlot()
{
	qDeleteAll(m_vcurve);
}

void MyPlot::settitle()
{
	QwtText t;
	t.setText(QObject::trUtf8("QwtPlot Test"));
	QFont font;
	font.setBold(true);
	font.setItalic(true);
	t.setFont(font);
	t.setColor(QColor(255, 0, 0));
	QBrush brush(QColor(0, 0, 255));
	t.setBackgroundBrush(brush);
	setTitle(t);
}


QRectF MyPlot::boundingRect()
{
	//return QGraphicsItem::boundingRect().adjusted(0, 0, 10, 10);
	return QRectF(0, 0, 110, 70);
}

void MyPlot::setXAxisScale(double dFreq,double dBW,bool bReplot)
{
	if(d_cfreq != dFreq || d_bw != dBW)
	{
		if(d_curve)
		{
			CircularBuffer* cb = (CircularBuffer*)d_curve->data();
			if(cb)
			{
				double s = dFreq - dBW / 2.0;
				double e = dFreq + dBW / 2.0;

				d_cfreq = dFreq;
				d_bw = dBW;

				cb->setXAxisScale(s,e);
				setAxisScale( QwtPlot::xBottom, s, e );

				if(bReplot)
					replot();
			}
		}
	}
}

void MyPlot::setData( const QVector< double >& coll )
{
	if(d_curve)
	{
		CircularBuffer* cb = (CircularBuffer*)d_curve->data();
		if(cb)
		{
			cb->setData(coll);

			//setAxisScale( QwtPlot::yLeft, min, max );

			setMaxMarker(cb->getMaxValue());

			replot();
		}
	}
}

void MyPlot::setMaxMarker( const QPointF& pf )
{
	d_maxMarker->setValue(pf);
	d_maxMarker->setLabel( QString( "[%1,%2]" ).arg(pf.x(),0,'f',4).arg(pf.y(),0,'f',2) );
}

//void MyPlot::inivcurve()
//{
//	for (int i = 0; i < 16; i++)
//	{
//		QwtPlotCurve * curve = new QwtPlotCurve();
//		curve->attach(this);
//		m_vcurve.push_back(curve);
//	}
//}

void MyPlot::updata()
{
	for (int i = 0; i < m_vcurve.size(); i++)
		m_vcurve[i]->setSamples(0, 0, 0);
	m_min = 0;
	m_max = 0;
}

QVector<QPointF> MyPlot::GetPoints(const QVector< double >& coll, const double &dFreq, const double &dBW)
{
	QVector<QPointF> tmp;
	double x = 0, y = 0;
	double dSFreq = dFreq - dBW / 2.0;
	double dEFreq = dFreq + dBW / 2.0;

	const int sz = coll.size();
	for (int i = 0; i < sz; i++)
	{
		if (sz > 1 && i >= 0 && i < sz)
		{
			x = dSFreq + (dEFreq - dSFreq) * i / (sz - 1);
			y = coll[i];
		}
		tmp.push_back(QPointF(x, y));
	}

	setXAxisScale2(dSFreq, dEFreq);
	return tmp;
}

void MyPlot::setXAxisScale2(double dSFreq, double dEFreq)
{
	m_min = m_min < dSFreq ? m_min : dSFreq;
	m_max = m_max > dEFreq ? m_max : dEFreq;

	setAxisScale(QwtPlot::xBottom, m_min, m_max);
}

void MyPlot::setData(int ID, const QVector< double >& coll, const double &dFreq,const double &dBW)
{
	m_vcurve[ID]->setSamples(GetPoints(coll, dFreq, dBW));

	replot();
}

void MyPlot::mousePressEvent(QMouseEvent *event)
{
	QwtPlot::mousePressEvent(event);
	event->accept();
}