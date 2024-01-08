#include "Month.h"
constexpr Month operator""_month(long double val)
        {
            return Month(static_cast<int>(val));
        }