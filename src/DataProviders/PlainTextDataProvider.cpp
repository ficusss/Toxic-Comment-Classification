#include "DataProvider.h"
#include<iostream>
#include<fstream>
#include<string>

std::vector<json> tcc::KaggleDataProvider::get_data() const
{
    std::vector<json> result = {};
    std::string line, text;
    std::infile in(_input_file);
    json j;
    while(std::getline(in, line))
    {
        if (!line.find_first_not_of("\t\v\r\n"))
        {
            text.append(line);
        }
    }
    j["comment_text"] = text;
    result.push_back(j);
    return result;
}
