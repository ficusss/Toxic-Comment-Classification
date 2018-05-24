#include "src\Controllers\Controller.h"
#include <iostream>
#include <memory>


int main()
{
	// testing
	//std::string input_train_file_name = "test_data/train.csv";
	// demonstration
	std::string input_train_file_name = "demonstration_data/train.csv";

	std::string input_test_file_name = "demonstration_data/test.txt";
	std::string output_file_name = "demonstration_data/output.txt";

	auto train_provider = std::make_shared<tcc::KaggleDataProvider> (tcc::KaggleDataProvider(input_train_file_name));
	auto test_provider = std::make_shared<tcc::PlainTextDataProvider>(tcc::PlainTextDataProvider(input_test_file_name));
	auto consumer = std::make_shared<tcc::StreamDataWriter> (tcc::StreamDataWriter(output_file_name));

	auto controller = tcc::Controller(train_provider, test_provider, consumer);
	controller.init();
	controller.run();

	return 0;
}