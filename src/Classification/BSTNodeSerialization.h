#ifndef BSTNODESERIALIZATION_H
#define BSTNODESERIALIZATION_H
#include "BSTNode.h"
#include <fstream>

namespace tcc
{
	/**
	@brief Запись дерева в файл
	@param node - указатель на корневой узел дерева
	@param out - поток для записи
	*/
	void serialize(BSTNode* node, std::ofstream &out);

	/**
	@brief Запись дерева в файл
	@param in - поток для чтения
	@return указатель на корневой узел дерева
	*/
	BSTNode* deserialize(std::ifstream &in);

}
#endif // BSTNODESERIALIZATION_H
