#ifndef BSTNODESERIALIZATION_H
#define BSTNODESERIALIZATION_H
#include "BSTNode.h"
#include <fstream>
#include <stdlib.h>

namespace tcc
{
	/**
	@brief Запись дерева в файл
	@param node - указатель на корневой узел дерева
	@param out - поток для записи
	*/
	void serialize(BSTNode* node, FILE *out);

	/**
	@brief Запись дерева в файл
	@param in - поток для чтения
	@return указатель на корневой узел дерева
	*/
	BSTNode* deserialize(FILE *in);

}
#endif // BSTNODESERIALIZATION_H
