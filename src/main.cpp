/**
* \file
* \brief Run file
*/

#include "Controllers\Controller.h"
#include <iostream>
#include <memory>
#include <time.h>
#include "phrases.h"

/**
@brief Check exist file
@param[in] filename Name of file to checking
@return (0 - Exist, 1 - No Exist)
*/
bool check_file(char* filename) {
	std::ifstream file;
	file.open(filename);
	if (!file)
		return 1;
	return 0;
		
}

/**
@brief Main function
@param  argc Arguments count
@param  argv Arguments value
@return Error code
*/
int main(int argc, char* argv[])
{
	std::cout << APP_START << argv[0] << std::endl;

	if (argc < 4)
	{
		std::cout << INSUFFICIENT_ARGS << std::endl;
	}
	else 
	{
		std::string input_test_filename = argv[1];
		std::string output_filename = argv[2];
		char* model_filename = argv[3];

		if (check_file(argv[1]))
		{
			std::cout << NOT_FOUND_FILE << argv[1] << std::endl;
			return 0;
		}
		if (check_file(model_filename))
		{
			std::cout << NOT_FOUND_FILE << model_filename << std::endl;
			return 0;
		}
		

		auto test_provider = std::make_shared<tcc::PlainTextDataProvider>(tcc::PlainTextDataProvider(input_test_filename));
		auto consumer = std::make_shared<tcc::StreamDataWriter> (tcc::StreamDataWriter(output_filename));

		auto controller = tcc::Controller(model_filename, test_provider, consumer);
		controller.run();

		std::cout << SUCCESSFUL_CONPLETION << std::endl;
		std::cout << CHECK_RESULT << argv[2] << std::endl;
	}
	
	return 0;
}