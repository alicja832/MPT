#pragma once
#include <string>

class Day{
    
    public:
    constexpr explicit Day(int day):_day{day}
    {

    }
    constexpr Day(const Day& other):_day{other._day}
        {}
    friend std::ostream& operator<<(std::ostream& o,const Day y)
        {
            if(y._day<10)
              o<<"0"+std::to_string(y._day);
            else
                o<<y._day;
            return o;
        } 
    
    private:
        int _day;
};
constexpr Day operator""_day(unsigned long long int val);
constexpr Day operator""_day(unsigned long long int val){
    return Day(static_cast<int>(val));
}