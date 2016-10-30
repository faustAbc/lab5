#include <iostream>
#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>
using namespace std;

double integral1(double x)
{ 
	return sin(0.4 * x) * pow(x, 0.23);
}


double integral2(double x)
{
	double value = sin(0.4 * x);
	 
	return pow(M_E, -x * x) * value * value / (x * x + 3.5);
}


double integral3(double x)
{
	return pow(M_E, 1.1 * x / (1 + x * x)) / (x * x + 1.1);
}


unsigned int comput(double integral(double), double acc)
{
	unsigned int part = 2;//количество частей
	const double xn = 1, xNull = 0;
	double step;//начальное разбиение на шаг
	double f = 0;//значение ф-ии
	double value = xNull;

	double differ = 0, tmp = 0;
	int time = clock();
	do
	{
		part <<= 1;
		step = xn / part;//сделать чтобы первый раз не инициалиизировать в цикле
		f = 0;
		value = xNull;
		while (value < xn)
		{
			f += step * ((integral(value) + integral(value + step)) / 2);
			value += step;
		}
		differ = f - tmp;
		tmp = f;
	} while (abs(differ) > acc);//можно без модуля!?
	time -= clock();
	cout << "Time: " << -time << " ms";
	cout << "\nIntegral: " << tmp;
	return part;
}


int main()
{
	char plus;//для зацикливания
	do
	{
		double acc = 0;
		do
		{
			cout << "Enter accuracy(from 0.1 to 0.0000001): ";
			cin >> acc;
			/*if (acc >= 1 || acc < 0.0000001)
				cout << "Incorrect value!\n";*/
		} while (acc >= 1 || acc < 0.0000001);
		cout << "Whitch integral you want to comput? Press:\n"
			"(1) to comput first integral\n"
			"(2) to comput second integral\n"
			"(3) to comput rhird integral\n";
		int choice;
		cout << "Your choice: ";
		cin >> choice;
		double x = 0;
		double(*myChoice)(double) = 0;
		switch (choice)
		{
		case 1:
			myChoice = integral1;
			break;
		case 2:
			myChoice = integral2;
			break;
		case 3:
			myChoice = integral3;
			break;
		}
		cout << "\nNumber of divisions: " << comput(myChoice, acc);
		cout << "\nPress '+' to restart or any other bottom to close the program: " << endl;
		
		cin >> plus;
		system("cls");
	} while (plus == '+');

    return 0;
}

