#pragma once

#include <iostream>
#include <string>
#include "includes/json.hpp"
#include "Classification/BOW.h"


using json = nlohmann::json;
/**
namespace tcc
@brief Пространство имен tcc
*/
namespace tcc
{
	///Перечисление "специальной" метаинформации о слове 
	enum word_info{ LOWERCASE, UPPERCASE, QUOTES};

	/// Cтруктура, описывающая слово
	typedef struct word {
		///слово
		std::string str;
		///мета-информация
		word_info info;
	}word_t;

	/**
	@brief Интерфейс для классов, предназначенных для нахождения основы слова (стемминга)
	*/
	class Stemmer {
	public:
		/**
		@brief Виртуальная функция для стемминга
		@param text Структура данных, содержащая в себе текст, подлежащий стеммингу
		@return Структура данных, содержащая в себе слова, приведенные к начальной форме
		*/
		virtual tcc::BOW stem(std::vector<json> text) = 0;
		virtual std::vector<std::string> stem_string_to_vec(std::string text) = 0;
	};
	/**
	@brief Стеммер Портера
	*/
	class PorterStemming: public Stemmer {
	public:
		/**
		@brief Функция, реализующая Стеммер Портера
		@param text Структура данных, содержащая в себе текст, подлежащий стеммингу
		@return Структура данных, содержащая в себе слова, приведенные к начальной форме
		*/
		tcc::BOW stem(std::vector<json> text);
		std::vector<json> tcc::PorterStemming::stem_for_print(std::vector<json> text);
		std::vector<std::string> stem_string_to_vec(std::string text);

	private:
		void trim(std::string& word);
		void stem_word(std::string& word);
		void ignore(std::string& word);
		size_t firstNonVowelAfterVowel(const std::string& word, size_t start);
		size_t getStartR1(const std::string& word);
		size_t getStartR2(const std::string& word, size_t startR1);
		void changeY(std::string& word);
		void step0(std::string& word);
		bool step1A(std::string& word);
		void step1B(std::string& word, size_t startR1);
		void step1C(std::string& word);
		void step2(std::string& word, size_t startR1);
		void step3(std::string& word, size_t startR1, size_t startR2);
		void step4(std::string& word, size_t startR2);
		void step5(std::string& word, size_t startR1, size_t startR2);
		inline bool isShort(const std::string& word);
		bool special(std::string& word);
		bool isVowel(char ch);
		bool isVowelY(char ch);
		bool endsWith(const std::string& word, const std::string& str);
		bool endsInDouble(const std::string& word);
		bool replaceIfExists(std::string& word, const std::string& suffix,
		const std::string& replacement, size_t start);
		bool isValidLIEnding(char ch);
		bool containsVowel(const std::string& word, size_t start, size_t end);
	};
}