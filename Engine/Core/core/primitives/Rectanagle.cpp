#include "Rectanagle.hpp"
#include <iostream>
#include <cmath>
#include <iostream>
namespace Primitives
{
    Rectanagle::verticies_array Rectanagle::rotateVertices()
    {
        Rectanagle::verticies_array rotated_vertices = {};
        for (int i = 0; i < 4; i++)
            rotated_vertices[i] = {verticies_arr[i].x, verticies_arr[i].y};
        float px = (rotated_vertices[0].x + rotated_vertices[1].x) / 2;
        float py = (rotated_vertices[0].y + rotated_vertices[3].y) / 2;
        for (int i = 0; i < 4; i++)
        {
            float x1 = rotated_vertices[i].x;
            float y1 = rotated_vertices[i].y;
            rotated_vertices[i].x = px + (x1 - px) * cos(angle) - (y1 - py) * sin(angle);
            rotated_vertices[i].y = py + (x1 - px) * sin(angle) + (y1 - py) * cos(angle);
        }
        return rotated_vertices;
    }
    void Rectanagle::calculateMatrixes()
    {
        const int &width = window->getWindowWidth();
        const int &height = window->getWindowHeight();
        auto vertices = rotateVertices();
        float vert_ptr[] = {
            vertices[0].x / float(width) - 1.0f, vertices[0].y / float(height) - 1.0f,
            vertices[1].x / float(width) - 1.0f, vertices[1].y / float(height) - 1.0f,
            vertices[2].x / float(width) - 1.0f, vertices[2].y / float(height) - 1.0f,
            vertices[3].x / float(width) - 1.0f, vertices[3].y / float(height) - 1.0f};
        float vert[] = {
            /*    cords                   |    RGBA color                                                                       | TexturePos*/
            vert_ptr[0], vert_ptr[1], 0.0f, color_arr[0].color.r, color_arr[0].color.g, color_arr[0].color.b, color_arr[0].alpha, 1.0f, 1.0f,
            vert_ptr[2], vert_ptr[3], 0.0f, color_arr[1].color.r, color_arr[1].color.g, color_arr[1].color.b, color_arr[1].alpha, 0.0f, 1.0f,
            vert_ptr[4], vert_ptr[5], 0.0f, color_arr[2].color.r, color_arr[2].color.g, color_arr[2].color.b, color_arr[2].alpha, 0.0f, 0.0f,
            vert_ptr[6], vert_ptr[7], 0.0f, color_arr[3].color.r, color_arr[3].color.g, color_arr[3].color.b, color_arr[3].alpha, 1.0f, 0.0f};
        this->setVertexHandler(vert, sizeof(vert), this->inc, sizeof(this->inc));
    }
    void Rectanagle::calculateVerticesArr()
    {
        verticies_arr[0] = {x - width / 2, y - height / 2};
        verticies_arr[1] = {x + width / 2, y - height / 2};
        verticies_arr[2] = {x + width / 2, y + height / 2};
        verticies_arr[3] = {x - width / 2, y + height / 2};
    }
    Rectanagle::Rectanagle(float x, float y, float width, float height, float alpha)
        : Primitive(Primitive::prim_type::SQUARE)
    {
        for (int i = 0; i < 4; i++)
            color_arr[i] =
                ColorRGBAF{
                    {1.0f,
                     1.0f,
                     1.0f},
                    alpha};
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        calculateVerticesArr();
        window = &Global::WindowProperties::getInstance();
        calculateMatrixes();
    }
    Rectanagle::Rectanagle(const Rectanagle &s)
        : Primitive(s)
    {
        for (int i = 0; i < 4; i++)
        {
            this->verticies_arr[i] = PointF{s.verticies_arr[i].x, s.verticies_arr[i].y};
            this->color_arr[i] =
                ColorRGBAF{
                    {s.color_arr[i].color.r,
                     s.color_arr[i].color.g,
                     s.color_arr[i].color.b},
                    s.color_arr[i].alpha};
        }
        this->x = s.x;
        this->y = s.y;
        this->width = s.width;
        this->height = s.height;
        this->window = &Global::WindowProperties::getInstance();
        this->calculateMatrixes();
    }
    Rectanagle &Rectanagle::operator=(const Rectanagle &s)
    {
        this->TYPE = s.TYPE;
        for (int i = 0; i < 4; i++)
        {
            this->verticies_arr[i] = PointF{s.verticies_arr[i].x, s.verticies_arr[i].y};
            this->color_arr[i] =
                ColorRGBAF{
                    {s.color_arr[i].color.r,
                     s.color_arr[i].color.g,
                     s.color_arr[i].color.b},
                    s.color_arr[i].alpha};
        }
        this->x = s.x;
        this->y = s.y;
        this->width = s.width;
        this->height = s.height;
        this->window = &Global::WindowProperties::getInstance();
        this->calculateMatrixes();
        return *this;
    }
    void Rectanagle::setWidth(float width)
    {
        this->width = width;
        calculateVerticesArr();
        calculateMatrixes();
    }
    void Rectanagle::setHeight(float height)
    {
        this->height = height;
        calculateVerticesArr();
        calculateMatrixes();
    }
    void Rectanagle::setTexture(std::string data)
    {
        this->setTextureData(data);
    }
    void Rectanagle::setPosition(float x, float y)
    {
        this->x = x;
        this->y = y;
        calculateVerticesArr();
        if (isVisible())
            calculateMatrixes();
    }
    void Rectanagle::Move(float x, float y)
    {
        setPosition(this->x + x, this->y + y);
    }
    void Rectanagle::setR(float r)
    {
        for (auto &c : color_arr)
        {
            c[ColorType::RED] = r;
        }

        if (isVisible())
            calculateMatrixes();
    }
    void Rectanagle::setG(float g)
    {
        for (auto &c : color_arr)
        {
            c[ColorType::GREEN] = g;
        }
        if (isVisible())
            calculateMatrixes();
    }
    void Rectanagle::setB(float b)
    {
        for (auto &c : color_arr)
        {
            c[ColorType::BLUE] = b;
        }
        if (isVisible())
            calculateMatrixes();
    }
    Rectanagle::~Rectanagle()
    {
    }
    bool Rectanagle::isVisible()
    {
        const int &width = window->getWindowWidth();
        const int &height = window->getWindowHeight();
        if (x >= 0 || x <= width)
            if (y >= 0 || y <= height)
                return true;
        return false;
    }
    void Rectanagle::Display()
    {
        glBindTexture(GL_TEXTURE_2D, this->getTexture());
        glBindVertexArray(this->getVAO());
        glBindBuffer(GL_ARRAY_BUFFER, this->getVBO());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->getEBO());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    float Rectanagle::getX()
    {
        return x;
    }
    float Rectanagle::getY()
    {
        return y;
    }
    bool Rectanagle::isNear(float x, float y, float radius)
    {
        if (x > this->x - radius && x < this->x + radius)
            if (y > this->y - radius && y < this->y + radius)
                return true;
        return false;
    }
    void Rectanagle::setAlpha(float alpha)
    {
        for (auto &c : color_arr)
        {
            c[ColorType::ALPHA] = alpha;
        }
        if (isVisible())
            calculateMatrixes();
    }
    void Rectanagle::setRotation(float angle)
    {
        if (angle > 2 * M_PI)
            angle = angle - (2 * M_PI);
        if (angle < -2 * M_PI)
            angle = angle + (2 * M_PI);
        this->angle = angle;
        if (isVisible())
            calculateMatrixes();
    }
    float Rectanagle::getRotation()
    {
        return angle;
    }
    void Rectanagle::rotate(float angle)
    {
        setRotation(this->angle + angle);
    }
    void Rectanagle::setColor(float r, float g, float b, float alpha)
    {
        for (auto &c : color_arr)
        {
            c[ColorType::RED] = r; 
            c[ColorType::GREEN] = g;
            c[ColorType::BLUE] = b;
            c[ColorType::ALPHA] = alpha;
        }
        if (isVisible())
            calculateMatrixes();
    }
    void Rectanagle::SetVerticeColor(int index, float value, ColorType colorType)
    {
        color_arr[index][colorType] = value;
    }
}