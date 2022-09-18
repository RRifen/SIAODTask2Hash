#include "Storage.h"
#include <iostream>

Storage::Storage()
{
	capacity = 64; //2^6 вместимость по умолчанию
	cur_size = 0;
	collection = new Business[capacity];
};

int Storage::hash_function(int number)
{
	return number % capacity;
}

int Storage::quadratic_probe(int index_start, int attempt)
{
	return (index_start + attempt + 2 * attempt * attempt) % capacity; //Функция гарантирует отсутствие циклов
}

int Storage::insert(int number, std::string name, std::string founder)
{
	if (cur_size / (double)capacity >= 0.75) //Условие рехеширвоания
	{
		rehash();
	}
	int index_start = hash_function(number);
	int index = index_start;
	for (int i = 1; true; i++) 
	{
		if (collection[index].number != -1) //Если запись существует
		{
			if (collection[index].number == number) //Прерывание вставки, ведь ключ должны быть уникальны
			{
				return 1;
			}
			else
			{
				index = quadratic_probe(index_start, i); //Разрешение коллизии пробированием
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
			if (collection[index].number == number) //Удачный поиск
			{
				result = 0;
				return &collection[index];
			}
			else
			{
				index = quadratic_probe(index_start, i);
			}
		}
		else if(collection[index].deleted) //Если элемент был удален, то поиск продолжается
		{
			index = quadratic_probe(index_start, i);
		}
		else //Неудачный поиск
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
			if (collection[index].number == number) //Элемент найден, производится удаление
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
		else if (collection[index].deleted) //Если элемент был удален, то поиск продолжается
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
			print_entry(&collection[i]); //Вывод одной записи
		}
	}
}

void Storage::print_entry(Business* entry)
{
	std::cout << "Номер лицензии: " << entry->number << std::endl;
	std::cout << "Название предприятия: " << entry->name << std::endl;
	std::cout << "Учредитель: " << entry->founder << std::endl;
	std::cout << "---------------------------------------------------------" << std::endl;
}

std::string random_string()
{
	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"; //Допустмые символы для строк
	std::string result;
	int count = (rand() % 17) + 3; //В строке минимум 3, максимум 19 символов
	for (int i = 0; i < count; i++)
	{
		result += alphabet[rand() % 53]; //Случйный символ из алфавита допустимых символов
	}
	return result;
}

int Storage::generate_random(int count) //Генерация случайных записей
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
		if (collection_old[i].number != -1) //Копирование старого массива записей в новый
		{
			insert(collection_old[i].number, collection_old[i].name, collection_old[i].founder);
		}
	}
	delete[] collection_old; //Удаление старого массива
}