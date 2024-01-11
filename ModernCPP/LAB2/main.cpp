
//Implement struct or class that represents two dimensional data
//Implement two operators - one for accessing data 
//and the second that performs convertion from Celsius to Farenheit or Kelvin based 
//on given char 
#include <iostream>
#include <vector>
struct Array2d
{
    //Your code here
    int& operator[](size_t row,size_t col)
    {
        if(row*width+col>=data.size())
        {
            throw std::out_of_range("out of bounds");
        }
        return data[row*width+col];
    }
    double operator[](size_t row,size_t col,char inf)
    {
        if(row*width+col>=data.size())
        {
            throw std::out_of_range("out of bounds");

        }
        if(inf=='K')
            return data[row+col*height]+273.15;
         if(inf=='F')
            return data[row+col*height]* 9.0/5.0 + 32.0;
        return 0;
    }
    size_t width;
    size_t height;
    std::vector<int> data;
    int a,b;
};
int main()
{
    Array2d arr(2,2);
    arr.data = {1,2,3,4};
    std::cout<<arr[1,1]<<std::endl; //4
    std::cout<<arr[0,1,'K']; //276.15
    //std::cout<<arr[2,2]; //shouldn't work
}