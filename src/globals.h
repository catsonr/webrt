#ifndef GLOBALS_H
#define GLOBALS_H

#include <algorithm>

namespace rt
{
    // GLOBAL VARIABLES
    constexpr int CANVAS_WIDTH = 800;
    constexpr int CANVAS_HEIGHT = 600;

    constexpr float PI = 3.14159265358979323846f;
    constexpr float TWOPI = 6.283185482025146484375f;
    constexpr float ONE_OVER_PI = 0.31830988618379067154f;
    constexpr float ONE_OVER_TWOPI = 0.15915494309189533577f;
    
    constexpr int SPECTRUM_COLORSAMPLES = 3;

    // GLOBAL INLINES
    // solves quadratic equation given A, B, C, and t0 t1 variables
    // returns true if there were solutions and false otherwise
    constexpr bool solveQuadratic(float A, float B, float C, float* t0, float* t1)
    {
        float discriminant = B*B - 4.0f * A * C;
        if(discriminant < 0.0f) return false;
        float discriminant_sqrt = sqrtf(discriminant);

        float q = (B < 0) ? -0.5f * (B - discriminant_sqrt) : -0.5f * (B + discriminant_sqrt);

        *t0 = q / A;
        *t1 = C / q;

        if(*t0 > *t1) std::swap(*t0, *t1);
        
        return true;
    }
    // clamps value between (inclusive) [min, max]
    constexpr float clamp(float value, float min, float max)
    {
        if (value <= min)
            return min;
        else if (value >= max)
            return max;

        return value;
    }
    // computes i % mod for all integers
    constexpr int mod(int i, int mod)
    {
        int n = int(i / mod);
        i -= n * mod;
        
        if(i < 0) i += mod;
        
        return i;
    }
    // converts degrees to radians
    constexpr float radians(float degrees)
    {
        return (PI / 180.0f) * degrees;
    }
    constexpr float degrees(float radians)
    {
        return (180.0f / PI) * radians;
    }
} // rt

#endif