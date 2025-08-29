#pragma once

#include <math.h>

namespace rock
{
    struct vec2
    {
        float x{};
        float y{};

        vec2() = default;
        vec2(float x, float y) : x(x), y(y) {}

        inline vec2 operator+(vec2& other)
        {
            return vec2(x + other.x, y + other.y);
        }

        inline vec2 operator-(vec2& other)
        {
            return vec2(x - other.x, y - other.y);
        }

        inline vec2 operator*(vec2& other)
        {
            return vec2(x * other.x, y * other.y);
        }

        inline float length()
        {
            return sqrtf(x * x + y * y);
        }

        inline vec2 scale(float s)
        {
            x *= s;
            y *= s;
            return *this;
        }

        inline vec2 normalize()
        {
            float l = length();
            x = x / l; 
            y = y / l;
            return *this;
        }

        inline float dotProduct(vec2& other)
        {
            return x * other.x + y * other.y;
        }
    };
}