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
        serialize(node->left, out);
        serialize(node->right, out);
    }
}

BSTNode* _deserialize(std::vector<BSTNode*> &nodes, unsigned cur_ind, size_t min, size_t max)
{
    if (cur_ind >= nodes.size() - 1)
    {
        return nullptr;
    }
    BSTNode* node = nodes[cur_ind];
    if (node->w.word_hash > min && node->w.word_hash < max)
    {
        node->left = _deserialize(nodes, cur_ind + 1, min, node->w.word_hash);
        node->right = _deserialize(nodes, cur_ind + 1, node->w.word_hash, max);
        return node;
    }
    else
    {
        return nullptr;
    }
}

BSTNode* deserialize(std::ifstream &in)
{
    Word w;
    std::vector<BSTNode*> nodes;
    while(in.read((char*)&w, sizeof(w)))
    {
        nodes.push_back(new BSTNode(w));
    }
	auto min = std::numeric_limits<std::size_t>::min();
	auto max = std::numeric_limits<std::size_t>::max();
    _deserialize(nodes, 0, std::numeric_limits<std::size_t>::min(), std::numeric_limits<std::size_t>::max());
	nodes.front()->_calc_height();
    return nodes.front();
}

}
