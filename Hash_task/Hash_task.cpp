#include <iostream>
#include <Windows.h>
#include "Storage.h"


using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Storage a; // ������ ���-�������
	Business* entry; // �������� �� ������

	int choice; // ����� ������
	int number; // ����� ��������
	int flag; // ���� ���������� ���������� ��������

	string name; //�������� �����������
	string founder; // ����������

	cout << "��������� ��������� ���������� ���-�������." << endl;
	cout << "��������� ������� (������������������ ����� �����������):" << endl;
	cout << "-> ����� �������� (����)" << endl;
	cout << "-> ��������" << endl;
	cout << "-> ����������" << endl;
	do
	{
		cout << "---------------------------------------------------------" << endl;
		cout << "�������� ��������:" << endl;
		cout << "1 - �������� ������" << endl;
		cout << "2 - �������� �������� ������" << endl;
		cout << "3 - ����� ������" << endl;
		cout << "4 - ����� �������" << endl;
		cout << "5 - ������� ������" << endl;
		cout << "6 - ��������� ������" << endl;
		cout << "-> ";
		cin >> choice;
		cout << "---------------------------------------------------------" << endl;
		switch (choice)
		{
		case 1:
		{
			cout << "������� ����� ��������: ";
			cin >> number;
			cout << "������� �������� �����������: ";
			cin >> name;
			cout << "������� ����������: ";
			cin >> founder;
			flag = a.insert(number, name, founder);
			cout << "---------------------------------------------------------" << endl;
			if (flag)
			{
				cout << "����������� � ����� ������� �������� ��� ����������������" << endl;
				break;
			}
			else 
			{
				cout << "����������� ������� ��������� � �������" << endl;
			}
			break;
		}
		case 2:
		{
			cout << "������� ���������� ������������ �������: ";
			cin >> number;
			a.generate_random(number);
			break;
		}
		case 3:
		{
			cout << "������� ����� ��������: ";
			cin >> number;
			entry = a.search(flag, number);
			cout << "---------------------------------------------------------" << endl;
			if (flag)
			{
				cout << "������ �� �������" << endl;
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
			cout << "������� ����� ��������: ";
			cin >> number;
			flag = a.eliminate(number);
			cout << "---------------------------------------------------------" << endl;
			if (flag)
			{
				cout << "������ ������ �� ����������" << endl;
			}
			else
			{
				cout << "������ ������� �������" << endl;
			}
			break;
		}
		}
	} while (choice != 6);
}