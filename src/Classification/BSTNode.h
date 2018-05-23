#pragma once

#include<vector>
#include<array>
#include<algorithm>
#include<stack>
#include "includes/json.hpp"


using json = nlohmann::json;

#define RIGHT_LEFT 2
#define LEFT_RIGHT -2


/**
@brief Узел двоичного дерева поиска
*/

namespace tcc {
	/**
	@brief Структура с необходимой для классификатора информацией о слове
	*/

	struct Word {
		size_t word_hash;	/**< Уникальный хэш слова*/
		double freq;	/**< Встречаемость в тексте*/
		std::array<size_t, 6> categories_freq = {0, 0, 0, 0, 0, 0}; /**< Встречаемость в текстах, относящихся к категории */

		Word() {};
		Word(int hash, double f) : word_hash(hash), freq(f) {};
		Word(const Word& r) : word_hash(r.word_hash), freq(r.freq) {};
		void _update_freq(json tags) {
			freq++;
			auto i = 0;

			for (json::iterator it = tags.begin(); it != tags.end(); ++it)
			{				
				if (it.value())
					categories_freq[i]++;
				i++;

			}
		}
		const Word& operator= (Word& r) { word_hash = r.word_hash;  freq = r.freq; return r; }
	};

	/**
	@brief Структура узла дерева двоичного поиска
	*/
	struct BSTNode {
		Word w;
		BSTNode* left;
		BSTNode* right;
		int height;

		BSTNode(Word& r) { w = r; left = right = nullptr; height = 1; }
		BSTNode* _insert(BSTNode* w);
		BSTNode* _balance(BSTNode* pivot);
		BSTNode* _find(int key);

		void _release();
		static int _height(BSTNode* n) { if (n) return n->height; return 0; }
		static BSTNode* _rotate_left(BSTNode* pivot);
		static BSTNode* _rotate_right(BSTNode* pivot);
		void _calc_height() { height = std::max(_height(left), _height(right)) + 1; };
		static int _rotate_param(BSTNode* n) { return _height(n->right) - _height(n->left); };
	};
}

