#pragma once
#include <iostream>
class Month
{
    public:
        constexpr explicit Month(int month):_month{month}
        {

        }
        constexpr Month(const Month& other):_month{other._month}
        {}
        friend std::ostream& operator<<(std::ostream& o,const Month& y)
        {
            if(y._month<10)
              o<<"0"+std::to_string(y._month);
            else
                o<<y._month;
            return o;
        } 
        
    private:
        int _month;
};
constexpr Month operator""_month(unsigned long long int val)
        {
            return Month(static_cast<int>(val));
        }