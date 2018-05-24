#include "DataProvider.h"
#include <iostream>

const char* tcc::KaggleDataProvider::s_quot = "\",";
const char tcc::KaggleDataProvider::s_delim = ',';

json tcc::KaggleDataProvider::_sample_to_json(std::vector<std::string>& text, std::vector<bool>& ratings) const{
	auto json_tags = { "id", "comment_text", "rating" };
	auto classes = {"toxic", "severe_toxic", "obscene", "threat", "insult", "identity_hate" };
	json result;
	std::vector<std::pair<std::string, std::string>> tags_list;
	std::vector<std::pair<std::string, bool>> classes_list;

	if (ratings.size() < 6) {
		ratings.resize(6);
	}

	tags_list.resize(json_tags.size() - 1);
	std::transform(json_tags.begin(), json_tags.end() - 1, text.begin(), tags_list.begin(),
		std::make_pair<std::string, std::string&>);
	for (auto el : tags_list)
		result[el.first] = el.second;

	classes_list.resize(classes.size());
	std::transform(classes.begin(), classes.end(), ratings.begin(), classes_list.begin(),
		std::make_pair<std::string, bool>);
	for (auto el : classes_list)
		result[std::string("rating")][el.first] = el.second;

	return result;
}


std::string tcc::KaggleDataProvider::_parse_id(std::string& line) const{
	auto pos = line.find(s_delim, 0);
	auto result = line.substr(0, pos);
	line.erase(0, pos + 1);

	return result;
}

bool tcc::KaggleDataProvider::_parse_text(std::string& line, std::string& dst) const{
	size_t start = 0;
	auto pos = line.find(s_quot, start);
	
	while (pos != start && pos != std::string::npos && pos != line.size()) {
		start = pos;
		pos = line.find(s_quot, start);		
	}

	if (pos != line.size() && pos == start) {
		dst += line.substr(0, start);
		line.erase(0, start + 1);
		return true;
	}

	dst += line;
	return false;

}

std::vector<bool> tcc::KaggleDataProvider::_parse_rating(std::string& line) const{
	std::vector<bool> result;
	
	for (auto el : line) {
		if (el != s_delim)
			result.push_back(static_cast<bool&&>(el - '0'));
	}
	
	return result;
}

std::vector<json> tcc::KaggleDataProvider::get_data() const{
	std::ifstream src;
	std::vector<json> result = {};
	std::string line;
	
	src.open(_input_file, std::ifstream::in);
	if (src.fail()) //если не удалось открыть файл, возвращаем 0
		return result;

	try {
		int i = 0;
		while (src.good()) {
			std::vector<std::string> buff;
			if (!getline(src, line))
				break;
			buff.push_back(static_cast<std::string&&> (_parse_id(line)));
			std::string text = "";
			while (!_parse_text(line, text)) {
				if (!getline(src, line))
					break;
				while (!line.size()) getline(src, line);;
			}
			buff.push_back(text);
			auto ratings = _parse_rating(line);			
			result.push_back(static_cast<json&&> (_sample_to_json(buff, ratings)));
			std::cout << i << std::endl;
			i++;
		}
	}
	catch (std::bad_alloc) {
		src.close();
		//вывести какое-то сообщение
		return result;
	}

	src.close();

	return result;
}

