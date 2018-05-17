#pragma once

#include<functional>
#include<vector>
#include<list>
#include<memory>
#include<algorithm>
#include "BOW.h"

namespace tcc {
	/** @defgroup aliases Сокращения
	*  Сокращения для названий используемых типов
	*  @{
	*/

	/** @brief Положительное целое*/
	using uint = unsigned int;
	/** @brief Вектор положительных целых*/
	using vec = std::vector<uint>;
	/** @brief Массив текстов*/
	using text = std::vector<std::string>;
	/** @} */

	/**
	@brief Интерфейс класса, преобразующего текст в вектор
	*/
	class Features {
	public:
		/**
		@brief Оценка выраженности признака, задаваемого одним словом
		@param s текст
		@param f функция, с помощью которой оценивается выраженность признака
		*/		
		virtual uint extract_feature(std::string& s, std::function<double(double)> f) const = 0;
		/**
		@brief Оценка выраженности признака, задаваемого несколькими словами
		@param s текст
		@param f функция, с помощью которой оценивается выраженность признака
		*/
		virtual uint extract_feature(text& s, std::function<double(double)> f) const = 0;
		/**
		@brief Сжатие размерности
		@param dim желаемая размерность
		@param s текст
		@param f функция, с помощью которой производится сжатие
		*/
		virtual uint reduce_dimensions(uint dim, text& s, std::function<double(double)> f) const = 0;
		/**
		@brief Оценка расстояния между двумя текстами
		@param l, r тексты
		*/
		double metric(Features& l, Features& r);
		virtual ~Features() = default;
	};


	/**
	@brief Преобразование на основе bag-of-words
	*/
	class BOWFeatures : public Features {
	private:
		std::shared_ptr<BOW> _global;
		std::vector<uint> _non_zero_hash;
		std::vector<uint> _non_zero_val;
		
	public:
		/**
		@brief Конструктор экземпляра класса
		@param global - информация о словах, встречающихся в корпусе текстов
		*/
		BOWFeatures(std::shared_ptr<BOW> global): _global(global) {};
		~BOWFeatures() override = default;
	};
}

