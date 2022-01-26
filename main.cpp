/*
* Используя стек, решить следующую задачу.
* В текстовом файле LOG записано без ошибок логическое выражение (ЛВ) в следующей форме:
* <ЛВ> ::= True | False | (!<ЛВ> ) | (<ЛВ > ^ <ЛВ>) | (< ЛВ > v < ЛВ >)
* Например: (! (T ^ F) v (F v T)). Вычислить (как boolean) значение этого выражения.
* Знаки !, ^, v означают соответственно отрицание, конъюнкцию и дизъюнкцию.
* Для реализации АТД Стек использовать массив.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

#define SIZE 100 
char Stack[SIZE];
int t;

using namespace std;

void init() // инициализация стека 
{
	t = -1;
}

bool IsEmpty() // проверить, является ли стек пустым 
{
	return t == -1;
}

void Push(int a) // положить в стек 
{
	if (t == SIZE) // проверка на попытку занесения элемента в полный стек 
		throw "Ошибка! Попытка занесения значения в полный стек!";

	t = t + 1;
	Stack[t] = a;
}

int Pop() // забрать из стека 
{
	if (IsEmpty()) // проверка на попытку забрать элемент из пустого стека 
		throw "Ошибка! Попытка чтения из пустого стека!";

	int val = 0;
	val = Stack[t];
	t = t - 1;
	return(val);
}

int Top() // получить значение верхнего элемента стека 
{

	if (IsEmpty()) // проверка на попытку забрать элемент из пустого стека 
		throw "Ошибка! Попытка чтения из пустого стека!";

	return(Stack[t]);
}

string readStr(string fileName) // открытие и чтение текстового файла
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

bool resolve(string str) // решение ЛВ
{
	int num = -1; // значение  
	char sign = NULL; // знак действия 

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
	init(); // инициализация стека

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