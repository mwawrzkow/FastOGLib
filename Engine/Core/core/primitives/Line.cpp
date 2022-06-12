#include "Line.hpp"
#include <cassert>
namespace Primitives
{
    Line::BezierLine::BezierLine(PointI p0, PointI p1, PointI p2, PointI p3, BezierType bezierType)
    {
        this->p0 = p0;
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
        this->bezierType = bezierType;
    }
    Line::BezierLine::BezierLine(const BezierLine &other)
    {
        this->p0 = other.p0;
        this->p1 = other.p1;
        this->p2 = other.p2;
        this->p3 = other.p3;
        this->bezierType = other.bezierType;
    }
    Line::BezierLine &Line::BezierLine::operator=(const BezierLine &other)
    {
        this->p0 = other.p0;
        this->p1 = other.p1;
        this->p2 = other.p2;
        this->p3 = other.p3;
        this->bezierType = other.bezierType;
        return *this;
    }
}

namespace Primitives
{
    Line::Line(PointI p0, PointI p1, float width)
        : Primitive(Primitive::LINE),
          line{.straight = StraightLine{p0, p1}},
          lineType(STRAIGHT),
          width(width),
          window(&Global::WindowProperties::getInstance())
    {
        this->calculateVerticesArr();
        this->calculateMatrixes();
    }
    Line::Line(PointI p0, PointI p1, PointI p2, float width)
        : Primitive(Primitive::LINE),
          line{.bezier = BezierLine{p0, p1, p2}},
          lineType(LineType::BEZIER),
          width(width),
          window(&Global::WindowProperties::getInstance())

    {
        this->calculateVerticesArr();
        this->calculateMatrixes();
    }
    Line::Line(PointI p0, PointI p1, PointI p2, PointI p3, float width)
        : Primitive(Primitive::LINE),
          line{.bezier = BezierLine{p0, p1, p2, p3, BezierLine::QUADRATIC}},
          lineType(LineType::BEZIER),
          width(width),
          window(&Global::WindowProperties::getInstance())
    {
        this->calculateVerticesArr();
        this->calculateMatrixes();
    }
    Line::Line(const Line &other)
        : Primitive(other),
          line{.straight = other.line.straight},
          width(other.width),
          window(&Global::WindowProperties::getInstance())
    {
        this->calculateVerticesArr();
        this->calculateMatrixes();
    }
    Line &Line::operator=(const Line &other)
    {
        this->TYPE = other.TYPE;
        this->line.straight = other.line.straight;
        this->line.bezier = other.line.bezier;
        this->width = other.width;
        this->window = &Global::WindowProperties::getInstance();
        this->calculateVerticesArr();
        this->calculateMatrixes();
        return *this;
    }
    void Line::calculateVerticesArr()
    {
        if (this->lineType == STRAIGHT)
        {
            calculateVerticesArrStraight();
        }
        else if (this->lineType == BEZIER)
        {
            calculateVerticesArrBezier();
        }
    }
    void Line::setTexture(std::string texturePath)
    {
        this->setTextureData(texturePath);
    }
    
    void Line::calculateVerticesArrStraight()
    {
        this->verticies_arr.clear();
        //find point A and B perpingdicular to Line seperated by width/2
        PointI P0 = this->line.straight.p0;
        PointI P1 = this->line.straight.p1;
        float coreSlope = (P1.y - P0.y) / (P1.x - P0.x);
        float slope = -1/coreSlope;
        // Calculating offset 
        float b0 = P0.y - slope * P0.x;
        float b1 = P1.y - slope * P1.x;
        float x0A = P0.x - this->width / 2;
        float x0B = P0.x + this->width / 2;
        float x1A = P1.x - this->width / 2;
        float x1B = P1.x + this->width / 2;
        float y0A = slope * x0A + b0;
        float y0B = slope * x0B + b0;
        float y1A = slope * x1A + b1;
        float y1B = slope * x1B + b1;
        verticies_arr.push_back({x0A,y0A});
        verticies_arr.push_back({x0B,y0B});
        verticies_arr.push_back({x1B,y1B});
        verticies_arr.push_back({x1A,y1A});
    }
    void Line::calculateVerticesArrBezier()
    {
        assert(false); // <- not implemented
    }
    void Line::calculateMatrixes()
    {
        const int &width = window->getWindowWidth();
        const int &height = window->getWindowHeight();
        std::vector<float> vert_ptr = {
            verticies_arr[0].x / float(width) - 1.0f, verticies_arr[0].y / float(height) - 1.0f,
            verticies_arr[1].x / float(width) - 1.0f, verticies_arr[1].y / float(height) - 1.0f,
            verticies_arr[2].x / float(width) - 1.0f, verticies_arr[2].y / float(height) - 1.0f,
            verticies_arr[3].x / float(width) - 1.0f, verticies_arr[3].y / float(height) - 1.0f};

        std::vector<float> vert = {
            /*    cords                   |    RGBA color                                                                       | TexturePos*/
            vert_ptr[0], vert_ptr[1], 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
            vert_ptr[2], vert_ptr[3], 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
            vert_ptr[4], vert_ptr[5], 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
            vert_ptr[6], vert_ptr[7], 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f};
        std::vector<unsigned int> inc = {0, 1, 2, 0, 2, 3};
        this->setVertexHandler(&vert[0], vert.size() * sizeof(float), &inc[0], inc.size() * sizeof(float));
    }
    bool Line::isVisible()
    {
        return true;
    }
    bool Line::isNear(float x, float y, float r)
    {
        return true;
    }
    Line::~Line()
    {
    }
    void Line::Display()
    {
        glBindTexture(GL_TEXTURE_2D, this->getTexture());
        glBindVertexArray(this->getVAO());
        glBindBuffer(GL_ARRAY_BUFFER, this->getVBO());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->getEBO());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

}