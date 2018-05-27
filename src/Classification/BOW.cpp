#include<functional>
#include "Classification/BOW.h"
#include "BSTNodeSerialization.h"

namespace tcc {
	void BOW::add_word(std::string& w, json tags)
	{
		std::hash<std::string> hash_fn;


		auto node = _root->_find(hash_fn(w));
		if (node)
		{
			node->w._update_freq(tags);
		}
		else
		{
			node = new BSTNode(Word(hash_fn(w), 0));
			node->w._update_freq(tags);
			_root = _root->_insert(node);
		}
	}

	tcc::Word BOW::find_word(std::string& s)
	{
		std::hash<std::string> hash_fn;
		auto res = _root->_find(hash_fn(s));

		if (res)
			return res->w;

		return  Word(0, 0);
	}

	void BOW::save_to_file(const char* filename)
	{
		int i = 0;
		std::ofstream out(filename, std::ios_base::binary);
		tcc::serialize(_root, out);
		auto t = i;
	}

	void BOW::load_from_file(const char* filename)
	{
		std::ifstream in(filename, std::ios_base::binary);
		_root = tcc::deserialize(in);
	}
}