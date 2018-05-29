#include "DataProvider.h"
#include<iostream>
#include<fstream>
#include<string>
#include "../phrases.h"

const char* tcc::PlainTextDataProvider::s_delim = "-----";


std::vector<json> tcc::PlainTextDataProvider::get_data() const
{
    std::vector<json> result = {};
    std::string line, text;
    std::ifstream in(_input_file);
	int i = 1;
    while(std::getline(in, line))
    {
        if(!line.compare(s_delim))
        {
            json j;
            j["comment_text"] = text;
            text.clear();
            result.push_back(j);
			std::cout << i++ << READ_TEXT << std::endl;
        }
        else if (!line.find_first_not_of("\t\v\r\n"))
        {
            text.append(line);
        }
    }
    if (text.length())
    {
        json j;
        j["comment_text"] = text;
        result.push_back(j);
		std::cout << i++ << READ_TEXT << std::endl;
    }
    return result;
}
