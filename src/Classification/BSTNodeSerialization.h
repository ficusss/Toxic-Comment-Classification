#ifndef BSTNODESERIALIZATION_H
#define BSTNODESERIALIZATION_H
#include "BSTNode.h"
#include <fstream>

namespace tcc
{
void serialize(BSTNode* node, std::ofstream &out);

BSTNode* deserialize(std::ifstream &in);

}
#endif // BSTNODESERIALIZATION_H
