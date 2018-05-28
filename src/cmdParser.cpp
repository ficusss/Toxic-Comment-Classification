#include<iostream>
#include "../includes/json.hpp"
#include "Controllers/Controller.h"


json tcc::parse_cmd(int argc, char* argv[]) {
	json keys = { {"src", 0}, {"dst", 0} };
	//json keys;

	for (int i = 0; i < argc; i++) {
		if (keys.find(argv[i]) != keys.end()){
			if (*(keys.find(argv[i])) != 0) {
				return json("error");
			}
			keys[argv[i]] = argv[i + 1];
			i++;
		}
	}

	return keys;
}
