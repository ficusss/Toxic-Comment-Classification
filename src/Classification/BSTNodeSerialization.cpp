#include "BSTNodeSerialization.h"
#include <vector>
#include <limits>

namespace tcc
{

void serialize(BSTNode* node, FILE *out)
{
    if (node)
    {
		fwrite((char*)&node->w, sizeof(Word), 1, out);
		fwrite((char*)&node->height, sizeof(int), 1, out);
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

BSTNode* deserialize(FILE *in)
{
    Word w;
    std::vector<BSTNode*> nodes;
    unsigned index = 0;
    while(!feof(in))
    {
		fread((char*)&w, sizeof(Word), 1, in);
        nodes.push_back(new BSTNode(w));
		fread((char*)&nodes.back()->height, sizeof(int), 1, in);
    }
	_deserialize(nodes, index, std::numeric_limits<std::size_t>::min(), std::numeric_limits<std::size_t>::max());
    return nodes.front();
}

}
