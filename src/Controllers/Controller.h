#pragma once

#include <memory>
#include "DataProviders/DataProvider.h"
#include "Cores/Core.h"
#include "DataConsumers/StreamDataWriter.h"
#include "../Stemmer/Stemmer.h"

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
		std::shared_ptr<DataProvider> _data_provider;
		std::shared_ptr<StreamDataWriter> _consumer;
		RandomCore _core;
		std::vector<json> _data;
		bool _init;
		int _dims = 100;
		//std::vector<std::vector<double>> _results;

		std::vector<json> load_data(std::shared_ptr<DataProvider> provider) { return provider->get_data(); }
		void save() { *_consumer << _data; };
		void close() { *_consumer << _data; };
	public:
		/**
		@brief Конструктор класса
		@param data_provider Указатель на используемый провайдер
		*/
		Controller(std::shared_ptr<DataProvider> train_data_provider, std::shared_ptr<DataProvider> data_provider,
			std::shared_ptr<StreamDataWriter> consumer)
			: _train_data_provider(data_provider), _data_provider(data_provider), _consumer(consumer)
		{
			_init = 0;
			//добавить инициализацию ядра
		};
		/**
		@brief Инициализация классификатора
		*/
		void init() 
		{ 
			load_data(_train_data_provider);
			//stemming
			_core.trainLoop(); 
			_init = 1;
		};
		/**
		@brief Обработка текста
		*/
		void run()
		{
			//initializing
			if (!_init)
				init();
			
			//load data
			_data = load_data(_data_provider);
			
			// stemming
			auto stem = tcc::PorterStemming();
			auto stem_data = stem.stem(_data);
			
			// calculating
			// ...
			
			//save result
			save();
		};
	};
}
