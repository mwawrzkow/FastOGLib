#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP
#include "vertexHandler.hpp"
#include <math.h>
#include "Renderable.hpp"
#ifndef M_PI
// Strange but needed fix for M_PI not defined in math.h on Windows machines
#define M_PI 3.14159265358979323846
#endif
class Primitive : public VertexHandler
{
protected:
    enum prim_type
    {
        RECTANAGLE,
        TRIANGLE,
        SQUARE,
        LINE
    } TYPE;

public:
    Primitive(prim_type);
    Primitive(prim_type type, bool isDefaultPrimitive);
    Primitive(const Primitive &p);
    Primitive &operator=(const Primitive &p);
    virtual ~Primitive();
    float sin(float r);
    float cos(float r);
    virtual bool isVisible() = 0;
    virtual bool isNear(float, float, float) = 0;
};

#endif