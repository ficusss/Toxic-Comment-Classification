#pragma once

#include <memory>
#include "../DataProviders/DataProvider.h"
#include "../Cores/Core.h"
#include "../DataConsumers/StreamDataWriter.h"
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
		std::shared_ptr<DataProvider> _data_provider;
		std::shared_ptr<StreamDataWriter> _consumer;
		tcc::RandomCore _core;
		tcc::PorterStemming _stem;
		tcc::BOW _train_stem_data;
		std::vector<json> _res;

		std::vector<json> load_data(std::shared_ptr<DataProvider> provider) { return provider->get_data(); }
		void save() 
		{ 
			*_consumer << _res;
			_consumer->close();
		};
		void close() { *_consumer << _res; };
	public:
		/**
		@brief Конструктор класса
		@param data_provider Указатель на используемый провайдер
		@param filename Имя файла, из которого будет считана модель
		@param consumer Указатель на поток, в который будет вестись запись
		*/

		Controller(char* filename,
			std::shared_ptr<DataProvider> data_provider,
			std::shared_ptr<StreamDataWriter> consumer)
			: _data_provider(data_provider), _consumer(consumer)
		{
			_core = tcc::RandomCore(std::make_shared<tcc::BOW>(tcc::BOW(filename)), 6);
			_stem = tcc::PorterStemming();
		};
		/**
		@brief Обработка текста
		*/
		void run()
		{
			//load data
			std::vector<json> texts = load_data(_data_provider);
			_res = {};
			
			for (auto text : texts)
			{
				// stemming
				auto stem_text = _stem.stem_string_to_vec(text["comment_text"]);

				// calculating
				auto ratings = _core.run(stem_text);
				
				text["rating"]["toxic"] = ratings[0];
				text["rating"]["severe_toxic"] = ratings[1];
				text["rating"]["obscene"] = ratings[2];
				text["rating"]["threat"] = ratings[3];
				text["rating"]["insult"] = ratings[4];
				text["rating"]["identity_hate"] = ratings[5];

				_res.push_back(text);
			}

			//save result
			save();
		};
	};
}
