#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ostream>
#include "../includes/json.hpp"

using json = nlohmann::json;

namespace tcc {
	/**
	@brief Класс, записывающий данные в поток
	*/
	class StreamDataWriter {
	public:
		/**
		@brief Перечисление, хранящее информацию о текущем состоянии потока
		*/
		enum State {
			GOOD,	///<Ошибки не зарегистрированы 
			FORMAT_FAIL, ///<Не удалось преобразовать переменную для записи 
			WRITING_FAIL, ///<Не удалось записать в поток
			OPENING_FAIL, ///<Не удалось открыть файл
		};
		/**
		@brief Конструктор экземпляра класса
		@param file_name Имя файла для записи. При отсутсвии запись ведется в консоль
		*/
		StreamDataWriter(std::string& file_name) {
			_output = new std::ofstream(file_name);
			if (!_output->is_open())
				_cur_state = OPENING_FAIL;
		}

		StreamDataWriter() = default;

		/**
		@brief Конструктор экземпляра класса
		@param file_name Имя файла для записи. При отсутсвии запись ведется в консоль
		*/
		StreamDataWriter(const char* file_name) : StreamDataWriter(std::string(file_name)) {};

		/**
		@brief Информация о текущем состоянии потока
		@relatesalso StreamDataWriter::State
		*/
		State state() { return _cur_state; }

		/**
		@brief Запись в поток вектора элементов произвольного типа (один элемент - одна строка)
		@tparam T тип записываемых элементов
		@param vec_el ссылка на запсываемый вектор
		*/
		template<typename T>
		State operator<<(std::vector<T>& vec_el) {
			for (T el : vec_el) {
				if (_output) {
					*(_output) << json(el);
					*(_output) << '\n';
					_output->flush();
				}
				else
					std::cout << json(el) << std::endl;

				if (_output->rdstate() == std::ios::badbit) {
					_cur_state = State::FORMAT_FAIL;
					return _cur_state;
				}

				if (_output->rdstate() == std::ios::failbit) {
					_cur_state = State::WRITING_FAIL;
					return _cur_state;
				}
			}
			return _cur_state;
		};


		/**
		@brief Запись в поток элемента произвольного типа
		@tparam T тип записываемого эелемента
		@param el ссылка на запсиываемый элемент
		*/
		template<typename T>
		State operator<<(T& el) {
			if (_output) {
				*(_output) << json(el);
				_output->flush();
			}
			else {
				std::cout << json(el);
				return _cur_state;
			}

			if (_output->rdstate() == std::ios::badbit) {
				_cur_state = State::FORMAT_FAIL;
			}

			if (_output->rdstate() == std::ios::failbit) {
				_cur_state = State::WRITING_FAIL;
			}
			return _cur_state;

		};

		/**
		@brief Закрытие потока
		*/
		State close() {
			if (_output) {
				_output->close();
				delete _output;
			}
			return _cur_state;
		}
	private:
		std::ofstream* _output = nullptr;
		State _cur_state = GOOD;
	};
};


