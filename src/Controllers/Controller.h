#pragma once

#include <memory>
#include "DataProviders/DataProvider.h"
#include "Cores/Core.h"
#include "DataConsumers/StreamDataWriter.h"

/**
namespace tcc
@brief Пространство имен tcc
*/
namespace tcc {

	/**
	@brief Обработка аргументов командной строки
	@param argc количество аргументов
	@param argv указатель на массив с данными
	*/
	json parse_cmd(int argc, char* argv[]);

	/**
	@brief Основной класс контроллер управляющий ходом программы
	*/
	class Controller {
	private:
		std::shared_ptr<DataProvider> _train_data_provider;
		//препроцессор
		RandomCore _core;
		StreamDataWriter _consumer;
		int _dims = 100;
		std::vector<std::vector<double>> _results;

		void _process_data();
	public:
		/**
		@brief Конструктор класса
		@param data_provider Указатель на используемый провайдер
		*/
		Controller(std::shared_ptr<DataProvider> data_provider)
			: _train_data_provider(data_provider) {};
		/**
		@brief Инициализация классификатора
		*/
		void init() { _process_data(); _core.trainLoop(); };
		/**
		@brief Обработка текста
		*/
		void run(textVec& texts)
		{
			_results.push_back(_core.run(texts));
		};
		/**
		@brief Сохранить текущий результат
		*/
		void save() { _consumer << _results; };
		/**
		@brief сохранить то, что осталось в буфере перед выыходом
		*/
		void close() { _consumer << _results; };
	};
}
