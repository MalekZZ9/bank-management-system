#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsUtility
{
public:

	static string ConvertNumberToText(int Number)
	{

		if (Number >= 0 && Number <= 19)
		{
			string Arr[] = { "" , "One" , "Two" , "Three" , "Four" , "Five" , "Six" , "Seven" ,
				"Eight" , "Nine" , "Ten" , "Eleven" , "Twelve" , "Thirteen" , "Fourteen"
				, "Fifteen" , "Sixteen" , "Seventeen" , "Eighteen" , "Nineteen" };

			return Arr[Number] + " ";
		}

		if (Number >= 20 && Number <= 99)
		{
			string Arr[] = { "" , "" , "Twenty" , "Thirty" , "Forty" , "Fifty" , "Sixty" , "Seventy" , "Eighty" , "Ninety" };

			return Arr[Number / 10] + " " + ConvertNumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return "One Hundred " + ConvertNumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return ConvertNumberToText(Number / 100) + "Hundreds " + ConvertNumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return "One Thousand " + ConvertNumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return ConvertNumberToText(Number / 1000) + "Thousands " + ConvertNumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return "One Million " + ConvertNumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 9999999)
		{
			return ConvertNumberToText(Number / 1000000) + "Million " + ConvertNumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return "One Billion " + ConvertNumberToText(Number & 1000000000);
		}

		if (Number >= 2000000000 && Number <= 9999999999)
		{
			return ConvertNumberToText(Number / 1000000000) + "Billion " + ConvertNumberToText(Number % 1000000000);
		}

		else
			return "No Number !!!";

	}

	static void SRand()
	{
		srand((unsigned)time(NULL));
	}
	static int GetRandomNumber(int From, int To)
	{
		return rand() % (To - From + 1) + From;
	}

	enum enCharType { SmallLetter, CapitalLetter, Digit, SpecialChar, Mix };
	static char GetRandomCharacter(enCharType CharType)
	{
		switch (CharType)
		{
		case enCharType::SmallLetter:
			return char(GetRandomNumber(97, 122));


		case enCharType::CapitalLetter:
			return char(GetRandomNumber(65, 90));


		case enCharType::Digit:
			return char(GetRandomNumber(48, 57));


		case enCharType::SpecialChar:
			return char(GetRandomNumber(33, 47));


		case enCharType::Mix:
			return GetRandomCharacter((enCharType)GetRandomNumber(0, 2));

		default:
			return ' ';
		}
	}

	static string GenerateWord(enCharType CharType, int Length)
	{
		string Word = "";

		for (int i = 1; i <= Length; i++)
			Word += GetRandomCharacter(CharType);

		return Word;
	}

	static string GenerateKey(enCharType CharType)
	{
		string Key = "";

		Key += GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4) + "-";
		Key += GenerateWord(CharType, 4);

		return Key;
	}

	static void GenerateKeys(enCharType CharType, int NumberOfKeys)
	{
		for (int i = 1; i <= NumberOfKeys; i++)
			cout << "Key [" << i << "] : " << GenerateKey(CharType) << endl;
	}

	static void Swap(int& Num1, int& Num2)
	{
		int temp = Num1;
		Num1 = Num2;
		Num2 = temp;
	}

	static void Swap(double& Num1, double& Num2)
	{
		double temp = Num1;
		Num1 = Num2;
		Num2 = temp;
	}

	static void Swap(string& Str1, string& Str2)
	{
		string temp = Str1;
		Str1 = Str2;
		Str2 = temp;
	}

	static void Swap(clsDate& Date1, clsDate& Date2)
	{
		clsDate temp = Date1;
		Date1 = Date2;
		Date2 = temp;
	}

	static void ShuffleArray(int Arr[], int Length)
	{
		for (int i = 0; i < Length; i++)
			Swap(Arr[i], Arr[GetRandomNumber(0, Length - 1)]);
	}

	static void ShuffleArray(string Arr[], int Length)
	{
		for (int i = 0; i < Length; i++)
			Swap(Arr[i], Arr[GetRandomNumber(0, Length - 1)]);
	}

	static void FillArrayWithRandomNumbers(int Arr[], int Length, int From, int  To)
	{
		for (int i = 0; i < Length; i++)
			Arr[i] = GetRandomNumber(From, To);
	}

	static void FillArrayWithRandomWords(string Arr[], int Length, enCharType CharType, int WordLength)
	{
		for (int i = 0; i < Length; i++)
			Arr[i] = GenerateWord(CharType, WordLength);
	}

	static void FillArrayWithRandomKeys(string Arr[], int Length, enCharType CharType)
	{
		for (int i = 0; i < Length; i++)
			Arr[i] = GenerateKey(CharType);
	}

	static string Tabs(int NumberOfTabs)
	{
		string S1 = "";

		for (int i = 1; i <= NumberOfTabs; i++)
			S1 += "\t";

		return S1;
	}

	static string Encrypt(string Text, int Key = 2)
	{
		int Length = Text.length();

		for (int i = 0; i < Length; i++)
		{
			Text[i] = (char)(Text[i] + Key);
		}

		return Text;
	}

	static string Decrypt(string Text, int Key = 2)
	{
		int Length = Text.length();

		for (int i = 0; i < Length; i++)
		{
			Text[i] = (char)(Text[i] - Key);
		}

		return Text;
	}

};