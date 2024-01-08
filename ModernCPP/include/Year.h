#pragma once
#include <iostream>

class Year
{
    public:
        constexpr explicit Year(int year):_year{year}
        {

        }
        constexpr Year(const Year& other):_year{other._year}
        {}
        friend std::ostream& operator<<(std::ostream& o,const Year& y)
        {
            o<<y._year;
            return o;
        } 
       
    private:
        int _year;
};
constexpr Year operator""_year(unsigned long long int val)
        {
            return Year(static_cast<int>(val));
        }