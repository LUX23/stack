/*
* ��������� ����, ������ ��������� ������.
* � ��������� ����� LOG �������� ��� ������ ���������� ��������� (��) � ��������� �����:
* <��> ::= True | False | (!<��> ) | (<�� > ^ <��>) | (< �� > v < �� >)
* ��������: (! (T ^ F) v (F v T)). ��������� (��� boolean) �������� ����� ���������.
* ����� !, ^, v �������� �������������� ���������, ���������� � ����������.
* ��� ���������� ��� ���� ������������ ������.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

#define SIZE 100 
char Stack[SIZE];
int t;

using namespace std;

void init() // ������������� ����� 
{
	t = -1;
}

bool IsEmpty() // ���������, �������� �� ���� ������ 
{
	return t == -1;
}

void Push(int a) // �������� � ���� 
{
	if (t == SIZE) // �������� �� ������� ��������� �������� � ������ ���� 
		throw "������! ������� ��������� �������� � ������ ����!";

	t = t + 1;
	Stack[t] = a;
}

int Pop() // ������� �� ����� 
{
	if (IsEmpty()) // �������� �� ������� ������� ������� �� ������� ����� 
		throw "������! ������� ������ �� ������� �����!";

	int val = 0;
	val = Stack[t];
	t = t - 1;
	return(val);
}

int Top() // �������� �������� �������� �������� ����� 
{

	if (IsEmpty()) // �������� �� ������� ������� ������� �� ������� ����� 
		throw "������! ������� ������ �� ������� �����!";

	return(Stack[t]);
}

string readStr(string fileName) // �������� � ������ ���������� �����
{
	string str = "";
	fstream inOut;

	inOut.open(fileName, ios::in);
	char memory = NULL;

	while (!inOut.eof())
	{
		if (memory != NULL)
			str += memory;

		inOut >> memory;
	}

	inOut.close();
	return str;
}

bool resolve(string str) // ������� ��
{
	int num = -1; // ��������  
	char sign = NULL; // ���� �������� 

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '(')
		{
			Push(num);

			num = -1;
			sign = NULL;
		}

		else if ((str[i] == 'F') || (str[i] == 'T'))
		{
			bool val;

			if (str[i] == 'F')
				val = 0;

			else
				val = 1;

			if (sign == NULL)
				num = val;

			else
			{
				if (sign == '!')
					num = !val;

				else if (sign == '^')
					num = num && val;

				else if (sign == 'v')
					num = num || val;
			}

			sign = NULL;
		}

		else if (str[i] == '!')
			sign = '!';
		else if (str[i] == '^')
			sign = '^';

		else if (str[i] == 'v')
			sign = 'v';

		else if (str[i] == ')')
		{
			bool val = Pop();

			if (sign == '!')
				num = !num;

			else if (sign == '^')
				num = num && val;

			else if (sign == 'v')
				num = num || val;

			sign = NULL;
		}
	}

	return num;
};

int main()
{
	init(); // ������������� �����

	string S = readStr("LOG.txt");
	try
	{
		cout << S << " = " << resolve(S) << endl;
	}

	catch (const char* ErrMSG)
	{
		cout << ErrMSG;
		exit(EXIT_FAILURE);
	}

	system("PAUSE");
	return 0;
}