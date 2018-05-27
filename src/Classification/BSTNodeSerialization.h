#ifndef BSTNODESERIALIZATION_H
#define BSTNODESERIALIZATION_H
#include "BSTNode.h"
#include <fstream>
#include <stdlib.h>

namespace tcc
{
	/**
	@brief ������ ������ � ����
	@param node - ��������� �� �������� ���� ������
	@param out - ����� ��� ������
	*/
	void serialize(BSTNode* node, FILE *out);

	/**
	@brief ������ ������ � ����
	@param in - ����� ��� ������
	@return ��������� �� �������� ���� ������
	*/
	BSTNode* deserialize(FILE *in);

}
#endif // BSTNODESERIALIZATION_H
