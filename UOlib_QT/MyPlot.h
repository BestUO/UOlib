#ifndef _MYPLOT_H_
#define _MYPLOT_H_

#include <qwt_plot.h>
#include <QEvent>

class QwtPlotGrid;
class QwtPlotCurve;
class QwtPlotMarker;

class MyPlot: public QwtPlot
{
    Q_OBJECT

public:
    MyPlot( QWidget* = NULL );
	~MyPlot();
	void setXAxisScale(double dFreq,double dBW,bool bReplot);
	void setData( const QVector< double >& coll );

	void setMaxMarker( const QPointF& pf );
	
	void updata();
	void setData(int ID,const QVector< double >& coll, const double &dFreq, const double &dBW);
	void settitle();

private:
	QRectF boundingRect();
	//void inivcurve();
	void setXAxisScale2(double dSFreq, double dEFreq);
	QVector<QPointF> GetPoints(const QVector< double >& coll, const double &dFreq, const double &dBW);
	void mousePressEvent(QMouseEvent  * event);

private:
    QwtPlotGrid *		d_grid;
    QwtPlotCurve *		d_curve;

	QwtPlotMarker*		d_maxMarker;

	double				d_cfreq;
	double				d_bw;

	QVector<QwtPlotCurve *> m_vcurve;

	double				m_min;
	double				m_max;
};


#endif

