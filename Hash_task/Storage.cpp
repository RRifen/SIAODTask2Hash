#include "Storage.h"
#include <iostream>

Storage::Storage()
{
	capacity = 64; //2^6 ����������� �� ���������
	cur_size = 0;
	collection = new Business[capacity];
};

int Storage::hash_function(int number)
{
	return number % capacity;
}

int Storage::quadratic_probe(int index_start, int attempt)
{
	return (index_start + attempt + 2 * attempt * attempt) % capacity; //������� ����������� ���������� ������
}

int Storage::insert(int number, std::string name, std::string founder)
{
	if (cur_size / (double)capacity >= 0.75) //������� �������������
	{
		rehash();
	}
	int index_start = hash_function(number);
	int index = index_start;
	for (int i = 1; true; i++) 
	{
		if (collection[index].number != -1) //���� ������ ����������
		{
			if (collection[index].number == number) //���������� �������, ���� ���� ������ ���� ���������
			{
				return 1;
			}
			else
			{
				index = quadratic_probe(index_start, i); //���������� �������� �������������
			}
		}
		else
		{
			collection[index].name = name;
			collection[index].founder = founder;
			collection[index].number = number;
			collection[index].deleted = false;
			++cur_size;
			return 0;
		}
	}
};

Business* Storage::search(int &result, int number)
{
	int index_start = hash_function(number);
	int index = index_start;
	for (int i = 1; true; i++)
	{
		if (collection[index].number != -1)
		{
			if (collection[index].number == number) //������� �����
			{
				result = 0;
				return &collection[index];
			}
			else
			{
				index = quadratic_probe(index_start, i);
			}
		}
		else if(collection[index].deleted) //���� ������� ��� ������, �� ����� ������������
		{
			index = quadratic_probe(index_start, i);
		}
		else //��������� �����
		{
			result = 1;
			return nullptr;
		}
	}
};

int Storage::eliminate(int number)
{
	int index_start = hash_function(number);
	int index = index_start;
	for (int i = 1; true; i++)
	{
		if (collection[index].number != -1)
		{
			if (collection[index].number == number) //������� ������, ������������ ��������
			{
				collection[index].number = -1;
				collection[index].deleted = true;
				collection[index].name = "";
				collection[index].founder = "";
				--cur_size;
				return 0;
			}
			else
			{
				index = quadratic_probe(index_start, i);
			}
		}
		else if (collection[index].deleted) //���� ������� ��� ������, �� ����� ������������
		{
			index = quadratic_probe(index_start, i);
		}
		else
		{
			return 1;
		}
	}
}

void Storage::output()
{
	for (int i = 0; i < capacity; i++)
	{
		if (collection[i].number != -1)
		{
			print_entry(&collection[i]); //����� ����� ������
		}
	}
}

void Storage::print_entry(Business* entry)
{
	std::cout << "����� ��������: " << entry->number << std::endl;
	std::cout << "�������� �����������: " << entry->name << std::endl;
	std::cout << "����������: " << entry->founder << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
}

std::string random_string()
{
	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"; //��������� ������� ��� �����
	std::string result;
	int count = (rand() % 17) + 3; //� ������ ������� 3, �������� 19 ��������
	for (int i = 0; i < count; i++)
	{
		result += alphabet[rand() % 53]; //�������� ������ �� �������� ���������� ��������
	}
	return result;
}

int Storage::generate_random(int count) //��������� ��������� �������
{
	int number;
	std::string name;
	std::string founder;
	srand(time(NULL));
	for (int i = 0; i < count; i++)
	{
		number = rand();
		name = random_string();
		founder = random_string();
		this->insert(number, name, founder);
	}
	return 0;
}

void Storage::rehash()
{
	int old_capacity = capacity;
	capacity = capacity * 2;
	cur_size = 0;
	Business* collection_old = collection;
	collection = new Business[capacity];
	for (int i = 0; i < old_capacity; i++)
	{
		if (collection_old[i].number != -1) //����������� ������� ������� ������� � �����
		{
			insert(collection_old[i].number, collection_old[i].name, collection_old[i].founder);
		}
	}
	delete[] collection_old; //�������� ������� �������
}