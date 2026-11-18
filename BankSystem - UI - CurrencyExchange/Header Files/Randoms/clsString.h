#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsString
{
private:
	string _Value;

public:

	clsString()
	{
		_Value = "";
	}
	clsString(string Value)
	{
		_Value = Value;
	}

	void SetValue(string Value)
	{
		_Value = Value;
	}
	string GetValue()
	{
		return _Value;
	}
	_declspec(property(get = GetValue, put = SetValue)) string Value;

	static short Length(string S1)
	{
		return S1.length();
	};
	short Length()
	{
		return _Value.length();
	};

	static void PrintFirstLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;
		// ofcourse when i is zero in the loop it will be first letter so its true

		cout << "\nFirst Letters of this string :\n";
		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
				cout << S1[i] << endl;
			// here i must check two conditions one the avoid printing ' ' even if it is a first letter
			// and the second condition is to check if the letter is first letter

			IsFirstLetter = (S1[i] == ' ' ? true : false);  // to know if the next letter is a first letter or not
		}
	}
	void PrintFirstLetterOfEachWord()
	{
		PrintFirstLetterOfEachWord(_Value);
	}

	static string UpperFirstLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;

		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
				S1[i] = toupper(S1[i]);

			IsFirstLetter = (S1[i] == ' ' ? true : false);
		}

		return S1;
	}
	void UpperFirstLetterOfEachWord()
	{
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	static string LowerFirstLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;

		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
				S1[i] = tolower(S1[i]);

			IsFirstLetter = (S1[i] == ' ' ? true : false);
		}

		return S1;
	}
	void LowerFirstLetterOfEachWord()
	{
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	static string UpperAllString(string S1)
	{
		for (int i = 0; i < S1.length(); i++)
			S1[i] = toupper(S1[i]);

		return S1;
	}
	void UpperAllString()
	{
		_Value = UpperAllString(_Value);
	}

	static string LowerAllString(string S1)
	{
		for (int i = 0; i < S1.length(); i++)
			S1[i] = tolower(S1[i]);

		return S1;
	}
	void LowerAllString()
	{
		_Value = LowerAllString(_Value);
	}

	static char InvertLetterCase(char ch)
	{
		return	isupper(ch) ? tolower(ch) : toupper(ch);
	}
	static string InvertAllLettersCase(string S1)
	{
		for (int i = 0; i < S1.length(); i++)
			S1[i] = InvertLetterCase(S1[i]);

		return S1;
	}
	void InvertAllLettersCase()
	{
		_Value = InvertAllLettersCase(_Value);
	}

	static int CountCapitalLetters(string S1)
	{
		int Counter = 0;

		for (int i = 0; i < S1.length(); i++)
			if (isupper(S1[i]))
				Counter++;

		return Counter;
	}
	short CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	static int CountSmallLetters(string S1)
	{
		int Counter = 0;

		for (int i = 0; i < S1.length(); i++)
			if (islower(S1[i]))
				Counter++;

		return Counter;
	}
	short CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}

	enum enWhatToCount { All, Capital, Small, Punct, Digits };
	static int CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All)
	{
		if (WhatToCount == enWhatToCount::All)
			return S1.length();

		int Counter = 0;

		for (int i = 0; i < S1.length(); i++)
		{
			if (WhatToCount == enWhatToCount::Capital && isupper(S1[i]))
				Counter++;

			if (WhatToCount == enWhatToCount::Small && islower(S1[i]))
				Counter++;

			if (WhatToCount == enWhatToCount::Punct && ispunct(S1[i]))
				Counter++;

			if (WhatToCount == enWhatToCount::Digits && isdigit(S1[i]))
				Counter++;
		}

		return Counter;
	}
	int CountLetters(enWhatToCount WhatToCount = enWhatToCount::All)
	{
		return CountLetters(_Value, WhatToCount);
	}

	static short CountSpecificLetter(string S1, char Letter, bool MatchCase = true)
	{
		int Counter = 0;

		for (int i = 0; i < S1.length(); i++)
		{
			if (MatchCase)
			{
				if (Letter == S1[i])
					Counter++;
			}

			else
			{
				if (tolower(S1[i]) == tolower(Letter))
					Counter++;
			}
		}

		return Counter;
	}
	short CountSpecificLetter(char Letter, bool MatchCase = true)
	{
		return CountSpecificLetter(_Value, Letter, MatchCase);
	}

	static bool IsVowel(char Letter)
	{
		Letter = tolower(Letter);
		// insted of checking each letter and its invert
		// just invert from the begining and check one type


		return ((Letter == 'a') || (Letter == 'e') || (Letter == 'i') || (Letter == 'o') || (Letter == 'u'));
	}
	static short CountVowels(string S1)
	{
		int Counter = 0;

		for (int i = 0; i < S1.length(); i++)
			if (IsVowel(S1[i]))
				Counter++;

		return Counter;
	}
	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static void PrintAllVowels(string S1)
	{
		cout << "\n\nVowel in string are : ";

		for (int i = 0; i < S1.length(); i++)
			if (IsVowel(S1[i]))
				cout << S1[i] << "    ";
	}
	void PrintAllVowels()
	{
		PrintAllVowels(_Value);
	}

	static void PrintEachWord(string S1)
	{
		string Delimiter = " ";
		int pos = 0;
		string sWord = "";

		cout << "Your String Words Are :\n\n";
		while ((pos = S1.find(Delimiter)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);

			if (sWord != "")
				cout << sWord << endl;

			S1.erase(0, pos + Delimiter.length());
		}


		if (S1 != "")
			cout << S1 << endl; // to print the last word
	}
	void PrintEachWord()
	{
		PrintEachWord(_Value);
	}

	static short CountWords(string S1)
	{
		int Counter = 0, pos = 0;
		string Delimiter = " ", sWord = "";

		while ((pos = S1.find(Delimiter)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);

			if (sWord != "")
				Counter++;

			S1.erase(0, pos + Delimiter.length());
		}

		if (S1 != "")
			Counter++;

		return Counter;
	}
	short CountWords()
	{
		return CountWords(_Value);
	}

	static vector <string> Split(string S1, string delimiter)
	{
		vector <string> vString;

		int pos = 0;
		string sWord = "";

		while ((pos = S1.find(delimiter)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);

			if (sWord != "")
				vString.push_back(sWord);

			S1.erase(0, pos + delimiter.length());
		}


		if (S1 != "")
			vString.push_back(S1);

		return vString;
	}
	vector <string> Split(string delimiter)
	{
		return Split(_Value, delimiter);
	}

	static string TrimLeft(string S1)
	{
		for (int i = 0; i < S1.length(); i++)
			if (S1[i] != ' ')
				return S1.substr(i, S1.length() - i);
		// the substr function takes the stating index and the length not the ending index

		return "";
	}
	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string S1)
	{
		int length = S1.length();

		for (int i = length - 1; i >= 0; i--)
			if (S1[i] != ' ')
				return S1.substr(0, i + 1);

		return "";
	}
	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	static string Trim(string S1)
	{
		return TrimLeft(TrimRight(S1));
	}
	void Trim()
	{
		_Value = Trim(_Value);
	}

	static string JoinString(vector <string> vString, string Delimiter)
	{
		string S1 = "";

		for (string Element : vString)
			S1 += Element + Delimiter;

		return S1.substr(0, S1.length() - Delimiter.length());
	}
	static string JoinString(string StringArr[], int ArrLength, string Delimiter)
	{
		string S1 = "";

		for (int i = 0; i < ArrLength; i++)
			S1 += StringArr[i] + Delimiter;

		return S1.substr(0, S1.length() - Delimiter.length());
	}

	static string ReverseWords(string S1)
	{
		string S2 = "";

		vector <string> vString = Split(S1, " ");
		vector <string>::iterator iter = vString.end();

		while (iter != vString.begin())
		{
			iter--;
			S2 += *iter + " ";
		}

		S2.pop_back();

		return S2;
	}
	void ReverseWords()
	{
		_Value = ReverseWords(_Value);
	}

	static string ReplaceWord(string S1, string From, string To, bool MatchCase = true)
	{
		vector <string> vString = Split(S1, " ");

		for (string& Element : vString)
		{
			if (MatchCase)
			{
				if (Element == From)
					Element = To;
			}
			else
			{
				if (LowerAllString(Element) == LowerAllString(From))
					Element = To;
			}
		}

		return JoinString(vString, " ");
	}
	void ReplaceWord(string From, string To, bool MatchCase = true)
	{
		_Value = ReplaceWord(_Value, From, To, MatchCase);
	}

	static string RemovePunctuations(string S1)
	{
		string S2 = "";

		for (int i = 0; i < S1.length(); i++)
			if (!ispunct(S1[i]))
				S2 += S1[i];

		return S2;
	}
	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}
};