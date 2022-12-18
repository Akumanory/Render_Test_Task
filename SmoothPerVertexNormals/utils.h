#pragma once

#include <math.h>

namespace utils
{

    // ---------------
    // --- Methods ---
    // ---------------

    bool is_equal(double lhs, double rhs, double epsilon = 0.01)
    {
        if (std::fabs(lhs - rhs) < epsilon)
            return true;
        return false;
    }

    // ---------------
    // --- Structs ---
    // ---------------

    struct vec3
    {
        vec3() = default;
        vec3(double _x, double _y, double _z)
            : x(_x), y(_y), z(_z)
        {}

        // ---------------
        // --- Members ---
        // ---------------

        double x = 0.0f;
        double y = 0.0f;
        double z = 0.0f;

        // ---------------
        // -- Operators --
        // ---------------

        vec3 operator+ (vec3 const &obj) const
        {
            return vec3(x + obj.x, y + obj.y, z + obj.z);
        }
        vec3 operator- (vec3 const &obj) const
        {
            return vec3(x - obj.x, y - obj.y, z - obj.z);
        }

        bool operator== (vec3 const &obj) const
        {
            if (!is_equal(x, obj.x))
                return false;

            if (!is_equal(y, obj.y))
                return false;

            if (!is_equal(z, obj.z))
                return false;

            return true;
        }

        bool operator!= (vec3 const &obj) const
        {
            return !(*this == obj);
        }

        // ---------------
        // --- Methods ---
        // ---------------

        double magnitude() const
        {
            return std::sqrt(
                std::pow(x,2) +
                std::pow(y,2) +
                std::pow(z,2));
        }
    };
} // namespace utils
