#include "Square.hpp"
#include <iostream>
#include <cmath>
#include <iostream>
namespace Primitives
{
    Square::Square(float x, float y, float a, float alpha)
        : Rectanagle(x, y, a, a, alpha)
    {
        this->size = a;
        calculateVerticesArr();
        calculateMatrixes();
    }
    Square::Square(const Square &s)
        : Rectanagle(s)
    {
        this->size = s.size;
        this->setWidth(this->size);
        this->setHeight(this->size);
        this->window = &Global::WindowProperties::getInstance();
        this->calculateMatrixes();
    }
    Square &Square::operator=(const Square &s)
    {
        this->TYPE = s.TYPE;
        this->size = s.size;
        this->setWidth(this->size);
        this->setHeight(this->size);
        this->window = &Global::WindowProperties::getInstance();
        this->calculateMatrixes();
        return *this;
    }
    Square::~Square()
    {
    }
}