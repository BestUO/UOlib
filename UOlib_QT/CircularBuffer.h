#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

#include <qwt_series_data.h>
#include <qvector.h>


class CircularBuffer: public QwtSeriesData<QPointF>
{
public:
    CircularBuffer();

	void setXAxisScale(double dSFreq,double dEFreq);
	void setData( const QVector< double >& coll );
    
    virtual size_t size() const;
    virtual QPointF sample( size_t i ) const;

    virtual QRectF boundingRect() const;

	QPointF getMaxValue() const;
	QPointF getMinValue() const;

private:
    QVector<double>		d_values;
	
	double				d_sfreq;
	double				d_efreq;

	double				d_min;
	double				d_max;

	int					d_minIndex;
	int					d_maxIndex;
};


#endif
