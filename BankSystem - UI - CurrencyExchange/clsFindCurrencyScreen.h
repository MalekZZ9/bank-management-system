#pragma once
#include "clsScreen.h"
class clsFindCurrencyScreen :
    protected clsScreen
{
private:

    static void _PrintCurrencyCard(clsCurrency Currency)
    {
        cout << "\nCurrency Card:";
        cout << "\n___________________________________";
        cout << "\nCountry      : " << Currency.CountryName();
        cout << "\nCode         : " << Currency.CurrencyCode();
        cout << "\nName         : " << Currency.CurrencyName();
        cout << "\nRate(1$)     : " << Currency.Rate();
        cout << "\n___________________________________\n";
    }

    static void _ShowResult(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrencyCard(Currency);
        }
        else
            cout << "\nCurrency Was not Found :-(\n";
    }

public:
    static void ShowFindCurrencyScreen()
    {
        clsScreen::_DrawScreenHeader("\t    Find Currency Screen");

        short Answer;
        cout << "Find By: [1] Code or [2] Country ? ";
        Answer = clsInputValidate::ReadIntNumberBetween(1, 2);

        if (Answer == 1)
        {
            string CurrencyCode = "";
            cout << "Enter Currency Code : ";
            CurrencyCode = clsInputValidate::ReadString();

            clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
            _ShowResult(Currency);
        }
        else
        {
            string CountryName = "";
            cout << "Enter Country Name: ";
            CountryName = clsInputValidate::ReadString();

            clsCurrency Currency = clsCurrency::FindByCountryName(CountryName);
            _ShowResult(Currency);
        }
    }
};