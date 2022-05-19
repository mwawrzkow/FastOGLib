#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP
#include "vertexHandler.hpp"
#include <math.h>
#ifndef M_PI
//Strange but needed fix for M_PI not defined in math.h on Windows machines
#define M_PI        3.14159265358979323846
#endif
class Primitive : public vertexHandler
{
protected:
    enum prim_type
    {
        RECTANAGLE,
        TRIANGLE,
        SQUARE,
    } TYPE;
public:
    float sin(float r);
    float cos(float r);
    Primitive(prim_type);
    virtual bool isVisible() = 0;
    virtual bool isNear(float, float, float) = 0;
    virtual ~Primitive();
};

#endif