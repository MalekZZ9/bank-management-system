#pragma once
#include "clsScreen.h"
class clsUpdateCurrencyRateScreen :
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

public:

    static void ShowUpdateCurrencyRateScreen()
    {
        clsScreen::_DrawScreenHeader("\t     Update Currency Screen");

        string CurrencyCode = "";
        cout << "Enter Currency Code : ";
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
        _PrintCurrencyCard(Currency);


        char Answer = 'n';
        cout << "\n\nAre you sure you want to update the rate of this currency ? y/n ";
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            cout << "\nUpdate Currency Rate :\n";
            cout << "----------------------\n";

            float NewRate = 0;
            cout << "Enter New Rate : ";
            NewRate = clsInputValidate::ReadPositiveDoubleNumber();

            Currency.UpdateRate(NewRate);

            cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrencyCard(Currency);
        }
    }
};