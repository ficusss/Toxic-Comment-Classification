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
		Word(size_t hash, double f) : word_hash(hash), freq(f) {};
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
	};

	/**
	@brief Структура узла дерева двоичного поиска
	*/
	struct BSTNode {
		Word w;
		BSTNode* left;
		BSTNode* right;
		int height;

		BSTNode(Word r) { w = r; left = right = nullptr; height = 1; }
		BSTNode* _insert(BSTNode* w);
		BSTNode* _balance(BSTNode* pivot);
		BSTNode* _find(size_t key);
		bool check(size_t min, size_t max)
		{
			bool l = true; bool r = true;
			if (left)
				l = w.word_hash >= left->w.word_hash && w.word_hash >= min && w.word_hash <= max && left->check(min, w.word_hash);
			if (right)
				l = w.word_hash < right->w.word_hash && w.word_hash >= min && w.word_hash <= max && right->check(w.word_hash, max);
			return l && r;
		}
		void _release();
		static int _height(BSTNode* n) { if (n) return n->height; return 0; }
		static BSTNode* _rotate_left(BSTNode* pivot);
		static BSTNode* _rotate_right(BSTNode* pivot);
		void _calc_height() { height = std::max(_height(left), _height(right)) + 1; };
		static int _rotate_param(BSTNode* n) { return _height(n->right) - _height(n->left); };
	};
}

