#include "Controllers\Controller.h"
#include <iostream>
#include <memory>
#include <time.h>


int main(int argc, char* argv[])
{
	std::string input_test_filename = argv[1];
	std::string output_filename = argv[2];
	char* model_filename = argv[3];

	auto test_provider = std::make_shared<tcc::PlainTextDataProvider>(tcc::PlainTextDataProvider(input_test_filename));
	auto consumer = std::make_shared<tcc::StreamDataWriter> (tcc::StreamDataWriter(output_filename));

	auto controller = tcc::Controller(model_filename, test_provider, consumer);
	controller.run();

	return 0;
}