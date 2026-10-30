#pragma once
#include "clsScreen.h"
class clsCurrencyExchangeScreen :
    protected clsScreen
{
private:

    static clsCurrency _GetCurrency(string message)
    {
        string CurrencyCode;
        cout << message;
        CurrencyCode = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }

        return clsCurrency::FindByCurrencyCode(CurrencyCode);
    }

    static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
    {

        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.CountryName();
        cout << "\nCode          : " << Currency.CurrencyCode();
        cout << "\nName          : " << Currency.CurrencyName();
        cout << "\nRate(1$) =    : " << Currency.Rate();
        cout << "\n_____________________________\n\n";

    }

    static void _PrintCurrencyExchangeResult(float Amount, clsCurrency Currency1, clsCurrency Currency2)
    {

        _PrintCurrencyCard(Currency1, "Convert From:");

        float AmountInUSD = Currency1.ConvertToUSD(Amount);

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInUSD << " USD\n";

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }

        cout << "\nConverting from USD to:\n";

        _PrintCurrencyCard(Currency2, "To:");

        float AmountInCurrrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

        cout << Amount << " " << Currency1.CurrencyCode()
            << " = " << AmountInCurrrency2 << " " << Currency2.CurrencyCode();
    }

public:

    static void ShowCurrencyExchangeScreen()
    {
        char Answer = 'y';

        while (tolower(Answer) == 'y')
        {
            system("cls");
            clsScreen::_DrawScreenHeader("\t Currency Exchange Screen");

            clsCurrency Currency1 = _GetCurrency("Enter Currency Code 1 (From) : ");
            clsCurrency Currency2 = _GetCurrency("Enter Currency Code 2 (To) : ");
            
            float Amount;
            cout << "\nEnter Amount To Exchange : ";
            Amount = clsInputValidate::ReadPositiveDoubleNumber();

            _PrintCurrencyExchangeResult(Amount, Currency1, Currency2);

            cout << "\n\nDo you want to perform another currency exchange ? y/n ";
            cin >> Answer;
        }
    }
};