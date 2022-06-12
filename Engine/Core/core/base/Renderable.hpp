#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

class Renderable
{
public:
    virtual void Display() = 0;    
    virtual void setVertexHandler(float vertices[], int VerticesSize, unsigned int indices[], int indicesSize) = 0;
};
#endif