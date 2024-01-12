#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

class Regex
{
    public:
        Regex(std::string filename):_filename{filename}
        {
           
        }
        void timpestamp_refromatting()
        {
            _file.open(_filename,ios::in);
            if(!_file.is_open())
            {
                std::cout<<"Not open file";
                exit(0);
            }
            
            std::regex date_pattern("(\\d{4})-(\\d{2})-(\\d{2})");
            std::string format = "$3/$2/$1";
            std::string rezult;

            while ( std::getline (_file,line) )
            {
                if(std::regex_search(line,date_pattern))
                {
                    rezult=std::regex_replace(line,date_pattern,format);
                    std::cout << rezult << '\n';
                }
            }
            _file.close();
        }
        void error_log_extraction()
        {
            _file.open(_filename,ios::in);
            if(!_file.is_open())
            {
                std::cout<<"Not open file";
                exit(0);
            }
            std::regex error("ERROR",std::regex_constants::ECMAScript);

            while ( std::getline (_file,line) )
            {
                if(std::regex_search(line,error))
                    std::cout << line << '\n';
            }
            _file.close();
        }
        void log_file_validation()
        {
             _file.open(_filename,ios::in);
            if(!_file.is_open())
            {
                std::cout<<"Not open file";
                exit(0);
            }
            try{
                //to jeszcze do dodania!!
                std::regex pattern("(\\d{4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}) ([[])(\[[:upper:]]{4,7})] (\\w)");

                while ( std::getline (_file,line) )
                {
                    std::cout<<std::boolalpha;
                    std::cout<<std::regex_search(line,pattern);
                    std::cout<<std::endl;
                }
            }catch(std::regex_error e)
            {
                std::cout<<e.what()<<std::endl;
            }
            _file.close();
        }
    private:
        std::string line;
        std::string _filename;
        std::fstream _file;
};