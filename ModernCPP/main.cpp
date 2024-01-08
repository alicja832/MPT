/*
The goal of this exercise is to write a simple class representing date. A date can be created using 3 numbers:
representing day, month and year, but the order in which these values will occur depends on the date format.
The problem we encounter is that depending on the world region, the date format can vary, resulting in ambiguity.
We cannot be sure whether Date(5,10,2012) is meant to represent 5th October 2012 or rather 10th May 2012,
and how about when someone uses a format that starts with the year first like Date(2024, 1, 1).
The solution might be to create classes representing Day, Month, and Year, that cannot be constructed using implicit conversions.
Now we can create multiple constructors for the Date class so that multiple date formats are accepted. In this exercise
for simplification, we will accept such 3 date formats:
    1) Europe:  dd.mm.yyyy
    2) USA:     mm-dd-yyyy
    3) Japan:   yyyy/mm/dd
    (d - day, m - month, y - year).
Date instance can be printed to the console using <<operator, and date format while constructing the object is associated with
how the date will be displayed (see: expected output at the bottom) - for that, I suggest assigning at construction some additional
value that will store information which format to use while printing the date. To make our code cleaner, we will use user-defined literals
for constructing Date class objects. In that way, we don't need so many parentheses cluttering our code and when constructing
a date object, using an incorrect date format will result in a compilation error. Additionally, we can make user-defined literal
functions and appropriate classes constexpr where that is possible.
*/

#include <iostream>
#include "Date.h"

// uncomment below lines to check whether incorrect date format results in a compilation error
// #define MAKE_ERROR_1
// #define MAKE_ERROR_2

int main()
{
    // creating Day, Month, Year class objects

    std::cout << "Creating day, month, and year objects in an explicit way using a constructor:" << std::endl << std::endl;

    Day day(1);
    Month month(1);
    Year year(2024);

    std::cout << "Day of month: " << day << ", month of year: " << month << ", year: " << year << std::endl;

    std::cout << "\n********************************************************************************\n";

    // creating Date class objects with multiple constructors fitting appropriate date formats

    std::cout << std::endl << "Creating New Year's Day in EU, USA and Japan format:" << std::endl << std::endl;

    Date new_year_2024_EU_format(day, month, year);
    Date new_year_2024_US_format(month, day, year);
    Date new_year_2024_JPN_format(year, month, day);

#ifdef MAKE_ERROR_1
    // bellow line should result in compilation error
    Date new_year_2024(month, year, day); // no constructor like Date(Month,Year,Day)
#endif // MAKE_ERROR_1

    // printing date class objects to the console - print format associated with construction format

    std::cout << "The date of the New Year's Day in Poland: " << new_year_2024_EU_format << std::endl;
    std::cout << "The date of the New Year's Day in the USA: " << new_year_2024_US_format << std::endl;
    std::cout << "The date of the New Year's Day in Japan: " << new_year_2024_JPN_format << std::endl;

    std::cout << "\n********************************************************************************\n";
    
   
    // creating constexpr Day, Month, Year class objects

    std::cout << std::endl << "Testing constexpr Date:" << std::endl << std::endl;

    constexpr Day last_day(31);
    constexpr Month last_month(12);
    constexpr Year last_year(2023);

    // creating constexpr Date class object

    constexpr Date end_of_2023(last_year, last_month, last_day);

    std::cout << "New Year's Eve in Japan: " << end_of_2023 << std::endl;

    std::cout << "\n********************************************************************************\n";

    // using user-defined literals

    std::cout << std::endl << "Now using user-defined literals:" << std::endl << std::endl;
    
    Date thanksgiving_2024_usa(11_month, 28_day, 2024_year);

    std::cout << "In the USA people celebrate thanksgiving on " << thanksgiving_2024_usa << std::endl;

    Date polish_constitution_day(3_day, 5_month, 2024_year);

    std::cout << "In Poland, The Constitution Day is on " << polish_constitution_day << std::endl;

#ifdef MAKE_ERROR_2
    // bellow line should result in compilation error
    Date error_date(2023_year, 15_day, 12_month); // no constructor like Date(Year,Day,Month)
#endif // MAKE_ERROR_2

    // adding constexpr

    constexpr Date emperors_birthday_japan(2024_year, 2_month, 23_day);

    std::cout << "In Japan, The Emperor's Birthday is on " << emperors_birthday_japan << std::endl;

    return 0;
    
}

// expected output

/*
Creating day, month, and year objects in an explicit way using a constructor:

Day of month: 01, month of year: 01, year: 2024

********************************************************************************

Creating New Year's Day in EU, USA and Japan format:

The date of the New Year's Day in Poland: 01.01.2024
The date of the New Year's Day in the USA: 01-01-2024
The date of the New Year's Day in Japan: 2024/01/01

********************************************************************************

Testing constexpr Date:

New Year's Eve in Japan: 2023/12/31

********************************************************************************

Now using user-defined literals:

In the USA people celebrate thanksgiving on 11-28-2024
In Poland, The Constitution Day is on 03.05.2024
In Japan, The Emperor's Birthday is on 2024/02/23
*/