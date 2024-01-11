// This task is an easy one. Joshua is beginner programmer.
// He wants to make his code more friendly to other programmers.
// Help him make it happen using attributes.

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//PLEASE COMPILE WITH FLAGS -Wall -Wextra
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <iostream>
#include <algorithm>

//All functions are created by Joshua

int *sortArray(const int arr[], int len)
{
    int* sortedArray = new int[len];
    std::copy(arr, arr + len, sortedArray);
    std::sort(sortedArray, sortedArray + len);
    return sortedArray;
}

void printIsWeekdayOrWeekend(int day)
{
    switch (day) {
        case 1:
        case 2:
            std::cout << "It's the beginning of the week." << std::endl;
             [[fallthrough]];
        case 3:
        case 4:
            std::cout << "It's the middle of the week." << std::endl;
             [[fallthrough]];
        case 5:
            std::cout << "It's a weekday." << std::endl;
            break;
            [[fallthrough]];
        case 6:
        case 7:
            std::cout << "It's the weekend." << std::endl;
            break;
        default:
            std::cout << "Invalid day." << std::endl;
    }
}

double convertTemperatureFromCelsius(double temperature, char unit)
{
    [[maybe_unused]]double Kelvin = 273.15;
    double FarenheitSum = 32;
    double FarenheitMuliplier = 9.0/5.0;
    switch (unit)
    {
    case 'K':
        std::cout<<"Not implemented yet, sorry!!!";
        temperature = 0;
        break;
        [[fallthrough]];
    case 'F':
        temperature = temperature * FarenheitMuliplier + FarenheitSum;
        break;
    default:
        std::cout<<"Invalid unit!";
        break;
    }
    return temperature;
}

[[noreturn]]double superImportantFunction()
{
    throw "Not Implemented Yet";
}

//Assume that main isn't written by Joshua and that they also are beginner C++ programmer.
//Can you spot potential problems right away?

int main()
{
    const int array[] = {2,3,5,1,0};
    int len = 5;
    sortArray(array, len);

    std::cout << "Sorted array: ";
    for (int i = 0; i < len; ++i) {
        std::cout << array[i] << " "; //Why array isn't sorted??
    }
    printIsWeekdayOrWeekend(6); //Why does it produce so many warnings??
    std::cout<<convertTemperatureFromCelsius(5, 'F');
    try{
        superImportantFunction(); //Why it terminates my program?
    }catch(const char* msg)
    {
        std::cout<<std::endl;
        std::cout<<msg<<std::endl;
    }
    //possible memory leaks??
}
    

