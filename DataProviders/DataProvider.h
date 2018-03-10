#pragma once

#include "../DataTypes/Message.h"
#include <vector>


/**
@brief ��������� ��� ������� ����������/������ ������
*/
class DataProvider {
	/**
	@brief ����������� ������� ��� ���������� ������
	@return ������ �������� ������, ���������� � ���� ��������� ������
	@throw IOException ���������� ����������� ��� ��������� � ������� �����
	*/
	virtual std::vector<Message> get_data() const = 0;
	/**
	@brief ����������� ������� ��� ������ ������
	@param msg ��������� ������, ���������� � ���� ������ ���������� ������
	@return ������� ��������:
		- 0 ������ �� ��������
		- 1 ������ �������
	*/
	virtual bool save_data(const Message& msg) const = 0;
};

/**
@brief ����� ��� ����������/������ ������ ��/� ����(�)
*/
class FileDataProvider : public DataProvider {
private:
	std::vector<char> _input_file;
	std::vector<char> _output_file;

public:
	/**
	@brief ����������� ������
	@param input_file ��� ����� ��� ������
	@param output_file ��� ����� ��� ������
	*/
	FileDataProvider(std::vector<char> input_file, std::vector<char> output_file)
		: _input_file(input_file), _output_file(output_file)
	{};

	/**
	@brief ������� ��� ���������� ������ �� �����
	@return ������ �������� ������, ���������� � ���� ��������� ������
	@throw IOException ���������� ����������� ��� ��������� � ������� �����
	*/
	std::vector<Message> get_data() const override;

	/**
	@brief ������� ��� ������ ������ � ����
	@param msg ��������� ������, ���������� � ���� ������ ���������� ������
	@return ������� ��������:
		- 0 ������ �� ��������
		- 1 ������ �������
	*/
	bool save_data(const Message& msg) const override;
};

/*
class SQLProvider : public DataProvider {
	Message get_data() const override;
	bool save_data(const Message& msg) const override;
};
*/