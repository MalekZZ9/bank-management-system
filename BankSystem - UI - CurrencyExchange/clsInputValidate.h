#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsInputValidate
{
public:

	static bool IsNumberBetween(int Number, int From, int To)
	{
		return Number >= From && Number <= To;
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		return Number >= From && Number <= To;
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		if (clsDate::IsDate1AfterDate2(From, To))
			clsDate::SwapDates(From, To);

		return clsDate::CompareDates(Date, From) != clsDate::Before &&
			clsDate::CompareDates(Date, To) != clsDate::After;
	}

	static int ReadIntNumber(string InvalidInputMessage = "Invalid Number, Enter Again : ")
	{
		int Number = 0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits <streamsize> ::max(), '\n');
			cout << InvalidInputMessage;
		}

		return Number;
	}

	static int ReadPositiveIntNumber(string OutRangeInputMessage = "Number Is Not Positive, Enter Again : ")
	{
		int Number = 0;
		cin >> Number; 

		while (Number <= 0)
		{

			cout << OutRangeInputMessage;
			cin >> Number;

		};

		return Number;
	}

	static int ReadIntNumberBetween(int From, int To, string OutRangeInputMessage = "Number Is Not Within Range, Enter Again : ")
	{
		int Number = ReadIntNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << OutRangeInputMessage;
			Number = ReadIntNumber();
		}

		return Number;
	}

	static double ReadDoubleNumber(string InvalidInputMessage = "Invalid Number, Enter Again : ")
	{
		double Number = 0.0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << InvalidInputMessage;
		}

		return Number;
	}


	static double ReadPositiveDoubleNumber(string OutRangeInputMessage = "Number Is Not Positive , Enter Again : ")
	{
		double Number = 0;
		cin >> Number;

		while (Number <= 0)
		{

			cout << OutRangeInputMessage;
			cin >> Number;

		}

		return Number;
	}

	static double ReadDoubleNumberBetween(double From, double To, string OutRangeInputMessage = "Number Is Not Within Range, Enter Again : ")
	{
		double Number = ReadDoubleNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << OutRangeInputMessage;
			Number = ReadDoubleNumber();
		}

		return Number;
	}

	static bool IsValidDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}

	static string ReadString()
	{
		string S1 = "";

		getline(cin >> ws ,S1);

		return S1;
	}

};