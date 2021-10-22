#include <iostream>
#include "anomaly_detection_util.h"

//return E(x)
float expectedValue(float *x, int size)
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

float var(float *x, int size)
{
    float x1 = expectedValue(x, size);
    float u = expectedValue2Parms(x, x, size);
    return x1 - u;
}

float cov(float *x, float *y, int size)
{
    return expectedValue2Parms(x, y, size) - (expectedValue(x, size) * expectedValue(y, size));
}

void say()
{
    std::cout << "d" << std::endl;
}

int main()
{
    say();
    std::cout << "!" << std::endl;
    return 0;
}
