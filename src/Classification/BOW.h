#pragma once
#include "includes/json.hpp"

using json = nlohmann::json;

#include "BSTNode.h"

using textVec = std::vector<std::string>;

namespace tcc {
	/**
	@brief Класс для хранения информации о корпусе слов в виде мешка слов
	*/
	class BOW {
	public:
		/**
		@brief Конструктор экземпляра класса
		*/
		BOW() { _root = new tcc::BSTNode(std::move(Word(0, 0))); }
		/**
		@brief Добавление слова в словарь
		@param s - строка, содержащая слово
		*/
		void add_word(std::string& s, json tags);
		/**
		@brief Поиск информации о слове
		@param s - искомое слово
		@returns количество раз, когда слово встретилось в корпусе текстов
		*/
		Word find_word(std::string& s);
	private:
		BSTNode* _root;
	};
}