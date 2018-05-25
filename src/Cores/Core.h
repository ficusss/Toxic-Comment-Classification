#include "includes/json.hpp"

#include "Classification/Classifyer.h"
#include "Classification/BOW.h"

#define LABELS_COUNT 5


using json = nlohmann::json;
using labels = std::array<bool, 5>;
using labeledText = std::vector<std::pair<textVec, labels>>;

/**
namespace tcc
@brief Пространство имен tcc
*/
namespace tcc {
	/**
	@brief Интерфейс классов ядра для классификации "недоброжелательности" текста
	 */

	class Core {
	public:
		/**
		@brief Виртуальная функция классификации "недоброжелательности" текста
		@param t текст в виде вектора слов
		*/
		virtual std::vector<double> run(textVec& t) const = 0;
		/**
		@brief Запуск обучения
		*/
		virtual void trainLoop() = 0;
		virtual ~Core() {};
	};

	/**
	@brief Класс - ядро для классификации "недоброжелательности" текста
	*/
	class RandomCore : public Core {
	private:
		std::vector<std::shared_ptr<Classifyer>> _model;
	public:
		/**
		@brief Конструктор класса
		@param model вектор классификаторов, задающих используемую модель
		*/
		RandomCore(std::vector<std::shared_ptr<Classifyer>> model) { _model = model; }

		/**
		@brief Конструктор класса
		@param b мешок слов, на основе которого будет построен классификатор
		@param tags_count количество категорий в тексте
		*/
		RandomCore(std::shared_ptr<BOW> b, int tags_count)
		{
			for (auto i = 0; i < tags_count; i++)
			{
				_model.push_back(std::shared_ptr<Classifyer>(new NaiveBayesClassifyer(b, i)));
			}
		}
		RandomCore() = default;
		~RandomCore() override = default;

		/**
		@brief Функция классификации "недоброжелательности" текста
		@param t текст для анализа
		*/
		std::vector<double> run(textVec& t) const override;
		
		void trainLoop() override 
		{ for (auto el : _model) el->train(); }
	};
}
