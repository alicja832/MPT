#include "Regex.h"
#include <iostream>

using namespace std;
int main()
{
    Regex reg("regex_server_log.txt");
    std::cout<<"Timestamp Reformatting:"<<std::endl;
    std::cout<<"_____________________________________________________"<<std::endl;
    reg.timpestamp_refromatting();
    std::cout<<"_____________________________________________________"<<std::endl;
    std::cout<<"ERROR log extraction:"<<std::endl;
    std::cout<<"_____________________________________________________"<<std::endl;
    reg.error_log_extraction();
    std::cout<<"_____________________________________________________"<<std::endl;
    std::cout<<"Log File validation:"<<std::endl;
    std::cout<<"_____________________________________________________"<<std::endl;
    reg.log_file_validation();
}