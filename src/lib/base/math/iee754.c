#include "lib/base/math/iee754.h"

float ieee754_single(u4 value)
{
    float result;
    memcpy(&result, &value, sizeof(result));
    return result;
}

double ieee754_double(u8 value)
{
    double result;
    memcpy(&result, &value, sizeof(result));
    return result;
}
