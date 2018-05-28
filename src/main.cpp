#include "Controllers\Controller.h"
#include <iostream>
#include <memory>
#include <time.h>

bool check_file(char* file_name) {
	std::ifstream file;
	file.open(file_name);
	if (!file)
		return 1;
	return 0;
		
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	std::cout << "Запущено приложение: " << argv[0] << std::endl;

	if (argc < 4)
	{
		std::cout << "Недостаточно входных арументов." << std::endl;
	}
	else 
	{
		std::string input_test_filename = argv[1];
		std::string output_filename = argv[2];
		char* model_filename = argv[3];

		if (check_file(argv[1]))
		{
			std::cout << "Не найден следующий файл : " << argv[1] << std::endl;
			std::cout << "Выполнение завершилось неудачей :(" << std::endl;
			return 0;
		}
		if (check_file(model_filename))
		{
			std::cout << "Не найден следующий файл : " << model_filename << std::endl;
			std::cout << "Выполнение завершилось неудачей :(" << std::endl;
			return 0;
		}
		

		auto test_provider = std::make_shared<tcc::PlainTextDataProvider>(tcc::PlainTextDataProvider(input_test_filename));
		auto consumer = std::make_shared<tcc::StreamDataWriter> (tcc::StreamDataWriter(output_filename));

		auto controller = tcc::Controller(model_filename, test_provider, consumer);
		controller.run();

		std::cout << "\nПриложение успешно завершило работу." << std::endl;
		std::cout << "Результат смотрите в " << argv[2] << ". (записан в json формате)." << std::endl;
	}

	return 0;
}