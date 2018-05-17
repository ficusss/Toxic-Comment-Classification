#include<functional>
#include "Classification/BOW.h"

namespace tcc {
	BOW::BOW(textVec& texts)
	{
		std::hash<std::string> hash_fn;

		for (auto word : texts)
		{
			add_word(word);
		}
	}

	void BOW::add_word(std::string& w)
	{
		std::hash<std::string> hash_fn;

		auto node = _root->_find(hash_fn(w));
		if (node)
		{
			node->w._update_freq();
		}
		else
		{
			node = new BSTNode(Word(hash_fn(w), 1));
			_root->_insert(node);
		}
	}

	size_t BOW::find_word(std::string& s)
	{
		std::hash<std::string> hash_fn;

		return  _root->_find_value(hash_fn(s));
	}
}