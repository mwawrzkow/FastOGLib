#ifndef LINE_HPP
#define LINE_HPP
#include "../base/Primitive.hpp"
#include "../WindowProperties.hpp"
#include "../base/Point.hpp"
#include "../WindowProperties.hpp"
#include <vector>
namespace Primitives
{
    class Line : public Primitive
    {
    private:
        struct StraightLine
        {
            PointI p0;
            PointI p1;
        };
        struct BezierLine
        {
        public:
            PointI p0;
            PointI p1;
            PointI p2; // end point if BezierType == BezierType::Cubic otherwise control point
            PointI p3; // control point if BezierType == BezierType::Quadratic otherwise no use
            enum BezierType
            {
                QUADRATIC,
                CUBIC
            } bezierType;
            BezierLine(PointI p0, PointI p1, PointI p2, PointI p3 = {0,0}, BezierType bezierType = BezierType::CUBIC); // BezierType::Cubic by default
            BezierLine(const BezierLine &other);
            BezierLine &operator=(const BezierLine &other);
        };
        union ULine
        {
            StraightLine straight;
            BezierLine bezier;
        } line;
        enum LineType
        {
            STRAIGHT,
            BEZIER
        } lineType;
        typedef std::vector<PointF> verticies_vector;

    private:
        // void setVertexHandler(float vertices[], int VerticesSize, unsigned int indices[], int indicesSize) override; Code might work as well for line, override might be not needed

    public:
        Line(PointI p0, PointI p1, float width);
        Line(PointI p0, PointI p1, PointI p2, float width);
        Line(PointI p0, PointI p1, PointI p2, PointI p3, float width);
        Line(const Line &other);
        ~Line();
        Line &operator=(const Line &other);

        void setTexture(std::string);
        void Display() override;
        bool isVisible() override;
        bool isNear(float, float, float) override;
    private:
        void calculateVerticesArr();
        void calculateVerticesArrStraight();
        void calculateVerticesArrBezier();
        void calculateMatrixes();

    private:
        verticies_vector verticies_arr;
        float width;
        Global::WindowProperties *window;
    };

}
#endif