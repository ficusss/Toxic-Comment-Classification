#pragma once
#include "../includes/json.hpp"

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
		@brief Конструктор экземпляра класса из файла
		*/
		BOW(const char* filename) { load_from_file(filename); }
		/**
		@brief Добавление слова в словарь
		@param s - строка, содержащая слово
		@param tags - структура с тегами комментария, к которому относится данное слово
		*/
		void add_word(std::string& s, json tags);
		/**
		@brief Поиск информации о слове
		@param s - искомое слово
		@returns структура, содержащая информацию о встречаемости слова в данном корпусе
		*/
		Word find_word(std::string& s);
		/**
		@brief Сохранение словаря в файл
		@param filename - имя файла
		*/
		void save_to_file(const char* filename);
		/**
		@brief Загрузка словаря из файла
		@param filename - имя файла
		*/
		void load_from_file(const char* filename);
	private:
		BSTNode* _root;
	};
}