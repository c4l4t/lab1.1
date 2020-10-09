//https://github.com/c4l4t/lab1.1

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream>

using namespace std;

struct DATA {
	int long day = 0, month = 0, year = 0;
	int mm[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; //Массив хранящий кол. дней в каждом месяце
	void plus(DATA* dat, int i, DATA& x1); //Функция увеличения даты на один день
	void minus(DATA* dat, int i, DATA& x2); //Функция уменьшает дату на один день
	void v6(DATA* dat, int count); //Функция для 6 варианта
	void input(DATA* dat); //Функция чтения данных из файла
	void out(DATA* dat, int count); //Функция ввывода в консоль результатов работы программы
};

int main() {
	setlocale(LC_ALL, "Russian");
	int i = 0;
	char dt[255];
	int count = 0;
	char seps[] = " .,!?/";
	ifstream f("data.txt");
	while (!f.eof())
	{
		f.getline(dt, 255);
		count++;
	}
	f.close();
	DATA date;
	DATA x1;
	DATA* dat = new DATA[count];
	date.input(dat);
	cout << endl;
	date.out(dat, count);
	cout << endl;
	date.v6(dat, count);
	return 0;
}



void DATA::plus(DATA* dat, int i, DATA& x1)
{
	x1.day = dat[i].day;
	x1.month = dat[i].month;
	x1.year = dat[i].year;
	x1.day++;
	if (x1.day > mm[x1.month - 1])
	{
		x1.day = x1.day - mm[x1.month - 1];
		x1.month++;
		if (x1.month > 12)
		{
			x1.month = x1.month - 12;
			x1.year++;
		}
	}
};



void DATA::minus(DATA* dat, int i, DATA& x2)
{
	if (dat[i].year % 4 == 0 || dat[i].year % 100 != 0 && dat[i].year % 400 == 0) //проверка года на високостность
	{
		mm[1] = 29;
	}
	x2.day = dat[i].day;
	x2.month = dat[i].month;
	x2.year = dat[i].year;
	x2.day--;
	if (x2.day < 1)
	{
		if (x2.month == 1)
		{
			x2.day = 31; x2.month = 12; x2.year--;
		}
		else {
			x2.day = mm[x2.month - 2];
			x2.month--;
			if (x2.month < 1)
			{
				x2.month = 12;
				x2.year--;
			}
		}
	}
}
void DATA::v6(DATA* dat, int count)
{
	cout << "Вариант 6" << endl;
	cout << "№ " << " Дата " << "   " << "   Пред.дата" << endl;
	DATA x2;
	int i = 0;
	for (i = 0; i < count; i++)
	{
		if (dat[i].day != 0)
		{
			if ( dat[i].month == 1 && dat[i].day == 1)
			{
				cout << i + 1 << " " << dat[i].year << "." << dat[i].month << "." << dat[i].day << "  ";
				if (dat[i].day == 1)
				{
					x2.day = 31; x2.month = 12; dat[i].year--;
					cout << " " << dat[i].year << "." << x2.month << "." << x2.day << endl;
				}
			}
		}
	}
}

void DATA::input(DATA* dat) { //Функция чтения и записи данных из файла в массив.
	char date[255];
	char* word;
	int i = 0;
	char seps[] = " .,!?/";
	ifstream fin("data.txt");
	while (fin.getline(date, 255)) { //считывание из файла
		word = strtok(date, seps);
		while (word != NULL) { // заполняем массив данными
			dat[i].year = atoi(word);
			if (dat[i].year < 1) {
				cout << "Некорректные данные" << endl;
				dat[i].year = 0;
			}
			else
			{
				cout << "Год:" << dat[i].year;
			}
			word = strtok(NULL, seps);
			dat[i].month = atoi(word);
			if (dat[i].month < 1 || dat[i].month>12) {
				cout << "Некорректные данные" << endl;
				dat[i].month = 0;
			}
			else
			{
				cout << "||Месяц:" << dat[i].month;
			}
			word = strtok(NULL, seps);
			dat[i].day = atoi(word);
			if (dat[i].year % 4 == 0 || dat[i].year % 100 != 0 && dat[i].year % 400 == 0) //проверка года на високостность
			{
				mm[1] = 29;
			}
			if (dat[i].day > mm[dat[i].month - 1])
			{
				cout << "Некорректные данные" << endl;
				dat[i].day = 0;
			}
			else
			{
				cout << "||День:" << dat[i].day << endl;
			}
			word = strtok(NULL, seps);
			i++;
		}
	}
	fin.close();
}

void DATA::out(DATA* dat, int count)
{
	int i = 0;
	DATA x1, x2;
	cout << "№" << " " << "   Дата" << "     След.дата " << " Пред.дата" << endl;
	for (i = 0; i < count; i++)
	{
		DATA::plus(dat, i, x1);
		DATA::minus(dat, i, x2);
		if (dat[i].day != 0)
		{
			cout << i + 1 << "||" << dat[i].year << "." << dat[i].month << "." << dat[i].day;
			cout << "||" << x1.year << "." << x1.month << "." << x1.day;
			cout << "||" << x2.year << "." << x2.month << "." << x2.day << endl;
		}
	}
}