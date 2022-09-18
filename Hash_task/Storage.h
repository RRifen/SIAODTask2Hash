#ifndef STORAGE_H
#define STORAGE_H

#include <string>

struct Business //��������� ������� � �������
{
public:
	int number = -1;
	std::string name;
	std::string founder;
	bool deleted = false; //���� �������� (���� �� ������ �������)
};

class Storage
{
private:
	int capacity;
	int cur_size;
	Business* collection;
	int hash_function(int number);
	int quadratic_probe(int index_start, int attempt);
public:
	Storage();
	int insert(int number, std::string name, std::string founder);
	int eliminate(int number);
	Business* search(int &result, int number);
	void output();
	void print_entry(Business* entry);
	int generate_random(int count); //������� ��������� �������
	void rehash();
};

#endif