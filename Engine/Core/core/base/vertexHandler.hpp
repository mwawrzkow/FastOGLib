#ifndef vertexHandler_HPP
#define vertexHandler_HPP
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include "Renderable.hpp"
class VertexHandler : public Renderable
{
private:
    /* data */
    unsigned int VBO, VAO, EBO;
    unsigned int texture;

public:
    VertexHandler(bool isDefaultPrimitive);
    VertexHandler(const VertexHandler &other);
    VertexHandler &operator=(const VertexHandler &other);
    ~VertexHandler();
    void setVertexHandler(float vertices[], int VerticesSize, unsigned int indices[], int indicesSize) override;
    void setTextureData(const std::string);
    int getTexture();
    int getVBO();
    int getEBO();
    int getVAO();
};

#endif