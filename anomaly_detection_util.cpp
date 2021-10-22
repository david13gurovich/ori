/*
 * animaly_detection_util.cpp
 *
 * Author: 314617739 Ori Angel
 */

#include <cmath>
#include "anomaly_detection_util.h"

//return u=E(x)=avg
float avg(float *x, int size)
{
    float sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum = sum + x[i];
    }
    return (1 / size) * sum;
}
//return E(x*y)
float expectedValue2Parms(float *x, float *y, int size)
{
    float sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum = sum + (x[i] * y[i]);
    }
    return (1 / size) * sum;
}
// returns the variance of X and Y
float var(float *x, int size)
{
    float x1 = avg(x, size);
    float u = expectedValue2Parms(x, x, size);
    return x1 - u;
}
// returns the covariance of X and Y
float cov(float *x, float *y, int size)
{
    return expectedValue2Parms(x, y, size) - (avg(x, size) * avg(y, size));
}
// returns the Pearson correlation coefficient of X and Y
float pearson(float *x, float *y, int size)
{
    float cov1 = cov(x, y, size);
    return cov1 / (sqrt(var(x, size)) * sqrt(var(y, size)));
}

// performs a linear regression and return s the line equation
Line linear_reg(Point **points, int size)
{
    int pointsLength = sizeof(points) / sizeof(points[0]);
    float *xPoints = new float[pointsLength];
    float *yPoints = new float[pointsLength];

    for (int i = 0; i < pointsLength; i++)
    {
        xPoints[i] = points[i]->x;
        yPoints[i] = points[i]->y;
    }

    // float cov1=cov()
    float a = cov(xPoints, yPoints, pointsLength) / var(xPoints, pointsLength);
    float b = avg(yPoints, pointsLength) - a * avg(xPoints, pointsLength);
    Line *line = new Line(a, b);
    return *line;
}

// returns the deviation between point p and the line equation of the points
float dev(Point p, Point **points, int size)
{
    Line line = linear_reg(points, size);
    float yLine = line.a * p.x + line.b;
    return abs(yLine - p.y);
}
// returns the deviation between point p and the line
float dev(Point p, Line l)
{
    float yLine = l.a * p.x + l.b;
    return abs(yLine - p.y);
}
