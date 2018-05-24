#pragma once

#include <memory>
#include "DataProviders/DataProvider.h"
#include "Cores/Core.h"
#include "DataConsumers/StreamDataWriter.h"
#include "Stemmer/Stemmer.h"

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
		std::shared_ptr<BOW> _train_stem_data_ptr;
		tcc::PorterStemming _stem;
		tcc::RandomCore _core;
		tcc::BOW _train_stem_data;
		std::vector<json> _res, _train_data;
		bool _init;
		int _dims = 100;

		std::vector<json> load_data(std::shared_ptr<DataProvider> provider) { return provider->get_data(); }
		void save() { *_consumer << _res; };
		void close() { *_consumer << _res; };
	public:
		/**
		@brief Конструктор класса
		@param data_provider Указатель на используемый провайдер
		*/
		Controller(std::shared_ptr<DataProvider> train_data_provider,
			std::shared_ptr<DataProvider> data_provider,
			std::shared_ptr<StreamDataWriter> consumer)
			: _train_data_provider(train_data_provider), _data_provider(data_provider), _consumer(consumer)
		{
			_init = 0;
			_stem = tcc::PorterStemming();
		};
		/**
		@brief Инициализация классификатора
		*/
		void init() 
		{ 
			_train_data = load_data(_train_data_provider);
			_train_stem_data = _stem.stem(_train_data);
			_train_stem_data_ptr = std::make_shared<tcc::BOW> (_train_stem_data);
			_core = tcc::RandomCore(_train_stem_data_ptr, 5);
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
			std::vector<json> text = load_data(_data_provider);

			// stemming
			//auto stem_text = stem_string_to_vec(text);
			
			// calculating
			//auto ratings = _core.run(stem_text);
			//auto classes = { "toxic", "severe_toxic", "obscene", "threat", "insult", "identity_hate" };
			//std::vector<std::pair<std::string, double>> classes_list;
			//classes_list.resize(classes.size());
			//std::transform(classes.begin(), classes.end(), ratings.begin(), classes_list.begin(),
			//	std::make_pair<std::string, bool>);
			//for (auto el : classes_list)
			//	text[std::string("rating")][el.first] = el.second;

			_res = text;

			//save result
			save();
		};
	};
}
