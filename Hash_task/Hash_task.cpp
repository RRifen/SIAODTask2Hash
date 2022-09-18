#include <iostream>
#include <Windows.h>
#include "Storage.h"


using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Storage a; // Объект хэш-таблицы
	Business* entry; // Укзатель на запись

	int choice; // Номер выбора
	int number; // Номер лицензии
	int flag; // Флаг успешности выполнения операция

	string name; //Название предприятия
	string founder; // Учредитель

	cout << "Программа реализует управление хэш-таблцей." << endl;
	cout << "Структура записей (зарегистрированных малых предприятий):" << endl;
	cout << "-> Номер лицензии (ключ)" << endl;
	cout << "-> Название" << endl;
	cout << "-> Учредитель" << endl;
	do
	{
		cout << "---------------------------------------------------------" << endl;
		cout << "Выберите действие:" << endl;
		cout << "1 - добавить запись" << endl;
		cout << "2 - добавить случйные записи" << endl;
		cout << "3 - поиск записи" << endl;
		cout << "4 - вывод записей" << endl;
		cout << "5 - удалить запись" << endl;
		cout << "6 - завершить работу" << endl;
		cout << "-> ";
		cin >> choice;
		cout << "---------------------------------------------------------" << endl;
		switch (choice)
		{
		case 1:
		{
			cout << "Введите номер лицензии: ";
			cin >> number;
			cout << "Введите название предприятия: ";
			cin >> name;
			cout << "Введите учредителя: ";
			cin >> founder;
			flag = a.insert(number, name, founder);
			cout << "---------------------------------------------------------" << endl;
			if (flag)
			{
				cout << "Предприятие с таким номером лицензии уже зарегистрировано" << endl;
				break;
			}
			else 
			{
				cout << "Предприятие успешно добавлено в таблицу" << endl;
			}
			break;
		}
		case 2:
		{
			cout << "Введите количество генерируемых записей: ";
			cin >> number;
			a.generate_random(number);
			break;
		}
		case 3:
		{
			cout << "Введите номер лицензии: ";
			cin >> number;
			entry = a.search(flag, number);
			cout << "---------------------------------------------------------" << endl;
			if (flag)
			{
				cout << "Запись не найдена" << endl;
			}
			else
			{
				a.print_entry(entry);
				system("pause");
			}
			break;
		}
		case 4:
		{
			a.output();
			system("pause");
			break;
		}
		case 5:
		{
			cout << "Введите номер лицензии: ";
			cin >> number;
			flag = a.eliminate(number);
			cout << "---------------------------------------------------------" << endl;
			if (flag)
			{
				cout << "Данной записи не существует" << endl;
			}
			else
			{
				cout << "Запись успешна удалена" << endl;
			}
			break;
		}
		}
	} while (choice != 6);
}