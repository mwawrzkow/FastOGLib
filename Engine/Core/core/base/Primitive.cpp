
#include "Primitive.hpp"
#include <math.h>

// Primitive::Primitive(prim_type, float vert[], int sizofvert, int indc[], int sizofindc):VertexHandler(){
//     this->setVertexHandler(vert,sizofvert, indc, sizofindc);
// }
Primitive::Primitive(prim_type type,bool isDefaultPrimitive)
    : VertexHandler(isDefaultPrimitive)
{
    this->TYPE = type;
}
Primitive::Primitive(prim_type type)
    : VertexHandler(true)
{
    this->TYPE = type;
}
Primitive::Primitive(const Primitive &p)
    : VertexHandler(p)
{
    this->TYPE = p.TYPE;
}
Primitive &Primitive::operator=(const Primitive &p)
{
    this->TYPE = p.TYPE;
    return *this;
}
Primitive::~Primitive()
{
}
float Primitive::sin(float r)
{
    // check if sin is less than 0.00001 and greater than -0.00001
    float sin = sinf(r);
    if (sin < 0.00001f && sin > -0.00001f)
        return 0;
    else
        return sin;
}
float Primitive::cos(float r)
{
    // check if cos is less than 0.00001 and greater than -0.00001
    float cos = cosf(r);
    if (cos < 0.00001f && cos > -0.00001f)
        return 0;
    else
        return cos;
}