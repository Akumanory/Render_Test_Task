#include "utils.h"

namespace utils
{

    // ---------------
    // --- Methods ---
    // ---------------

    bool is_equal(double lhs, double rhs, double epsilon)
    {
        if (std::fabs(lhs - rhs) < epsilon)
            return true;
        return false;
    }

}