#include "Controllers\Controller.h"
#include <iostream>
#include <memory>
#include <time.h>


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

	time_t timer;
	auto start_time = time(&timer);

	controller.init();

	auto initend_time = time(&timer);

	controller.run();

	auto end_time = time(&timer);

	std::ofstream out("demonstration_data/time_working.txt");
	out << "init_time: " << difftime(initend_time, start_time) << std::endl;
	out << "run_time: " << difftime(end_time, initend_time) << std::endl;


	return 0;
}