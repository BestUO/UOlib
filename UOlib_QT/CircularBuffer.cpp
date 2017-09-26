#include "circularbuffer.h"
#include <qmath.h>


CircularBuffer::CircularBuffer()
{
	d_sfreq = 500;
	d_efreq = 800;

	d_min = 9999;
	d_max = -9999;

	d_minIndex = -1;
	d_maxIndex = -1;
}

void CircularBuffer::setXAxisScale(double dSFreq,double dEFreq)
{
	d_sfreq = dSFreq;
	d_efreq = dEFreq;
}

void CircularBuffer::setData( const QVector< double >& coll )
{
	d_values = coll;

	double min = 9999;
	double max = -9999;
	int minInd = -1;
	int maxInd = -1;

	for(int k = 0; k < coll.size(); ++k)
	{
		double d = coll[k];

		if(d < min)
		{
			min = d;

			minInd = k;
		}

		if(d > max)
		{
			max = d;

			maxInd = k;
		}
	}

	d_min = min;
	d_max = max;

	d_minIndex = minInd;
	d_maxIndex = maxInd;
}

size_t CircularBuffer::size() const
{
    return d_values.size();
}

QPointF CircularBuffer::sample( size_t i ) const
{
	double x = 0,y = 0;

    const int sz = d_values.size();
	if(sz > 1 && i >= 0 && i < sz)
	{
		x = d_sfreq + (d_efreq - d_sfreq) * i / (sz - 1); 
		y = d_values[i];
	}

    return QPointF(x,y);
}

QRectF CircularBuffer::boundingRect() const
{
    return QRectF( -1.0, -1, 2.0, 1 );
}

QPointF CircularBuffer::getMaxValue() const
{
	return sample(d_maxIndex);
}

QPointF CircularBuffer::getMinValue() const
{
	return sample(d_minIndex);
}

