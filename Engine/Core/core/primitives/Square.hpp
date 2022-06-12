#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "../base/Primitive.hpp"
#include "../WindowProperties.hpp"
#include "../base/Point.hpp"
#include "Rectanagle.hpp"
#include <memory>
#include <array>
namespace Primitives
{
    class Square : public Rectanagle
    {
    private:
    float size = 0; 
    public:
        Square(float, float, float, float = 1.0f);
        Square(const Square &s);
        Square &operator=(const Square &s);
        virtual ~Square();
    };

}

#endif
