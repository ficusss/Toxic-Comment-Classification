#include "src\Controllers\Controller.h"
#include <iostream>
#include <memory>
//#include "src\DataProviders\DataProvider.h"
//#include "src\DataConsumers\StreamDataWriter.h"

int main()
{
	std::string input_file_name = "demonstration_data/train.csv";
	std::string output_file_name = "demonstration_data/output.txt";
	auto provider = std::make_shared<tcc::KaggleDataProvider> (tcc::KaggleDataProvider(input_file_name));
	auto consumer = std::make_shared<tcc::StreamDataWriter> (tcc::StreamDataWriter(output_file_name));
	auto controller = tcc::Controller(provider, provider, consumer);

	controller.run();

	return 0;
}