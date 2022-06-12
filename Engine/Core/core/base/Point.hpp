#ifndef TYPES_HPP
#define TYPES_HPP
#include <stdexcept>

namespace Primitives
{
    enum ColorType{ 
        RED,
        GREEN,
        BLUE,
        ALPHA,
        ERROR, 
    };
    template <typename T>
    struct Point2D
    {
        T x = 0,
          y = 0;
    };
    typedef struct Point2D<float> PointF;
    typedef Point2D<int> PointI;
    typedef Point2D<double> PointD;
    typedef Point2D<unsigned int> PointU;
    typedef Point2D<unsigned long> PointUL;
    typedef Point2D<unsigned long long> PointULL;
    typedef Point2D<long> PointL;
    typedef Point2D<long long> PointLL;
    typedef Point2D<char> PointC;
    typedef Point2D<short> PointS;



    template <typename T>
    struct Color{ 
        T r = 0,
          g = 0,
          b = 0;
        T& operator[](ColorType type)
        {
            switch (type)
            {
            case ColorType::RED:
                return r;
            case ColorType::GREEN:
                return g;
            case ColorType::BLUE:
                return b;
            default:
                throw std::invalid_argument("Invalid color type");
                break;
            }
        }
    };
    typedef struct Color<float> ColorF;
    typedef Color<int> ColorI;
    typedef Color<double> ColorD;
    typedef Color<unsigned int> ColorU;
    typedef Color<unsigned long> ColorUL;
    typedef Color<unsigned long long> ColorULL;
    typedef Color<long> ColorL;
    typedef Color<long long> ColorLL;
    typedef Color<char> ColorC;
    typedef Color<short> ColorS;

    template <typename T>
    struct ColorRGBA{ 
        Color<T> color; 
        T alpha = 0;
        T& operator[](ColorType type)
        {
            switch (type)
            {
            case ColorType::ALPHA:
                return alpha;
            default:
                return color[type];
                break;
            }
        }
    };
    typedef struct ColorRGBA<float> ColorRGBAF;
    typedef ColorRGBA<int> ColorRGBAI;
    typedef ColorRGBA<double> ColorRGBAD;
    typedef ColorRGBA<unsigned int> ColorRGBAU;
    typedef ColorRGBA<unsigned long> ColorRGBAUL;
    typedef ColorRGBA<unsigned long long> ColorRGBAULL;
    typedef ColorRGBA<long> ColorRGBAL;
    typedef ColorRGBA<long long> ColorRGBALL;
    typedef ColorRGBA<char> ColorRGBAC;
    typedef ColorRGBA<short> ColorRGBAS;
}
#endif