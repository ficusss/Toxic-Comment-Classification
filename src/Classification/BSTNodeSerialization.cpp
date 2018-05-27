#include "BSTNodeSerialization.h"
#include <vector>
#include <limits>

namespace tcc
{

void serialize(BSTNode* node, std::ofstream &out)
{
    if (node)
    {
        out.write((char*)&node->w, sizeof(Word));
		out.write((char*)&node->height, sizeof(int));
        serialize(node->left, out);
        serialize(node->right, out);
    }
}

BSTNode* _deserialize(std::vector<BSTNode*> &nodes, unsigned &cur_ind, size_t min, size_t max)
{
    if (cur_ind >= nodes.size())
    {
        return nullptr;
    }
    BSTNode* node = nodes[cur_ind];
    if (node->w.word_hash >= min && node->w.word_hash <= max)
    {
        cur_ind++;
        node->left = _deserialize(nodes, cur_ind, min, node->w.word_hash);
        node->right = _deserialize(nodes, cur_ind, node->w.word_hash, max);
        return node;
    }
    return nullptr;
}

void _deserialize_naive(std::vector<BSTNode*> &nodes)
{
	for (auto it = nodes.begin() + 1; it != nodes.end(); it++)
	{
		nodes[0] = nodes[0]->_insert(*it);
	}
}

BSTNode* deserialize(std::ifstream &in)
{
    Word w;
    std::vector<BSTNode*> nodes;
    unsigned index = 0;
    while(in.read((char*)&w, sizeof(w)))
    {
		int t;
        nodes.push_back(new BSTNode(w));
		//in.read((char*)&nodes.back()->height, sizeof(int));
		in.read((char*)&t, sizeof(int));
    }
	// _deserialize(nodes, index, std::numeric_limits<std::size_t>::min(), std::numeric_limits<std::size_t>::max());
	_deserialize_naive(nodes);
	auto test = nodes.front()->check(std::numeric_limits<std::size_t>::min(), std::numeric_limits<std::size_t>::max());
    return nodes.front();
}

}
