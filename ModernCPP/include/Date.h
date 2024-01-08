#pragma once
#include <iostream>
#include "Month.h"
#include "Year.h"
#include "Day.h"

 enum data_format
    {
        EU = 0,
        US = 1,
        JPN = 2
    };

class Date
{
    public:
    constexpr Date(Day d,Month m,Year y):year{y},month{m},day{d},format{EU}
    {
        
    }
    constexpr Date(Month m,Day d,Year y):year{y},month{m},day{d},format{US}
    {

    }
    constexpr Date(Year y,Month m,Day d):year{y},month{m},day{d},format{JPN}
    {

    }
    friend std::ostream& operator<<(std::ostream& o,const Date& y)
    {
        switch(y.format) {
            case 0:
                o<<y.day<<"."<<y.month<<"."<<y.year;
            break;
            case 1:
                o<<y.month<<"-"<<y.day<<"-"<<y.year;
            break;
            case 2:
                o<<y.year<<"/"<<y.month<<"/"<<y.day;
            break;
        }
        return o;
    }
    
    private:
    Day day;
    Month month;
    Year year;
    data_format format;

};