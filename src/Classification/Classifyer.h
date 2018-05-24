#pragma once
#include <memory>
#include <cmath>
#include <vector>
#include <string>
#include <Classification/BOW.h>


namespace tcc {
	/**
	@brief Вектор текстов
	*/
	using textVec = std::vector<std::string>;
	/**
	@brief Вектор текстов с тегами
	*/
	using labeledText = std::vector<std::pair<textVec, bool>>;

	/**
	@brief Интерфейс классификатора текста
	*/
	class Classifyer {
	public:
		/**
		@brief Запуск обучения классификатора
		*/
		virtual void train() = 0;
		/**
		@brief Оценка текста
		@param text - текст, подлежащий оцениванию
		@returns вероятность принадлежности текста категории
		*/
		virtual double run(textVec& text) const = 0;
		virtual ~Classifyer() = default;
	};
	/**
	@brief Наивный байесовский классификатор
	*/
	class NaiveBayesClassifyer : public Classifyer {
	public:
		/**
		@brief Конструктор экземпляра класса
		@param v - информация о словах, встречающихся в корпусе текстов
		*/
		NaiveBayesClassifyer(std::shared_ptr<BOW>& v, int i) : bow(v), _ind(i) {};
		~NaiveBayesClassifyer() override = default;

		void train() override {};
		double run(textVec& text) const override;
	private:
		double _logLike(std::string& word) const;
		int _ind;
		std::shared_ptr<BOW> bow = nullptr;
	};
}