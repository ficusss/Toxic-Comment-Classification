#ifndef BSTNODESERIALIZATION_H
#define BSTNODESERIALIZATION_H
#include "BSTNode.h"
#include <fstream>

namespace tcc
{
	/**
	@brief ������ ������ � ����
	@param node - ��������� �� �������� ���� ������
	@param out - ����� ��� ������
	*/
	void serialize(BSTNode* node, std::ofstream &out);

	/**
	@brief ������ ������ � ����
	@param in - ����� ��� ������
	@return ��������� �� �������� ���� ������
	*/
	BSTNode* deserialize(std::ifstream &in);

}
#endif // BSTNODESERIALIZATION_H
