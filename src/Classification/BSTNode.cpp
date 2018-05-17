#include <ctime>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "BSTNode.h"


namespace tcc {

	BSTNode* BSTNode::_rotate_right(BSTNode* pivot) {
		auto pivot_left = pivot->left;

		pivot->left = pivot_left->right;
		pivot_left->right = pivot;

		pivot->_calc_height();
		pivot_left->_calc_height();

		return pivot_left;
	}

	BSTNode* BSTNode::_rotate_left(BSTNode* pivot) {
		auto pivot_right = pivot->right;

		pivot->right = pivot_right->left;
		pivot_right->left = pivot;

		pivot->_calc_height();
		pivot_right->_calc_height();

		return pivot_right;
	}


	BSTNode* BSTNode::_balance(BSTNode* pivot) {
		if (pivot) {
			pivot->_calc_height();

			if (_rotate_param(pivot) == RIGHT_LEFT) {
				if (_rotate_param(pivot->right) < 0)
					pivot->right = _rotate_right(pivot->right);

				return _rotate_left(pivot);
			}

			if (_rotate_param(pivot) == LEFT_RIGHT) {
				if (_rotate_param(pivot->left) > 0)
					pivot->left = _rotate_left(pivot->left);

				return _rotate_right(pivot);
			}
		}

		return pivot;
	}

	BSTNode* BSTNode::_find(int key) {
		auto curr_node = this;

		while (curr_node) {
			if (curr_node->w.word_hash == key)
				return curr_node;
			if (key > curr_node->w.word_hash)
				curr_node = curr_node->right;
			else
				curr_node = curr_node->left;
		}

		return nullptr;
	}

	BSTNode* BSTNode::_insert(BSTNode* inserted) {
		auto curr_node = this;
		auto parent = curr_node;
		std::stack<BSTNode*> path;

		while (curr_node) {
			path.push(curr_node);
			if (inserted->w.word_hash > curr_node->w.word_hash) {
				if (!curr_node->right) {
					curr_node->right = inserted;
					break;
				}
				curr_node = curr_node->right;
			}
			else {
				if (!curr_node->left) {
					curr_node->left = inserted;
					break;
				}
				curr_node = curr_node->left;
			}
		}


		while (!path.empty()) {
			parent = path.top();
			parent->left = _balance(parent->left);
			parent->right = _balance(parent->right);
			path.pop();
		}

		return _balance(parent);
	}

	void BSTNode::_release() {

		if (left) {
			left->_release();
			delete left;
			left = nullptr;
		}
		if (right) {
			right->_release();
			delete right;
			right = nullptr;
		}
	}

}