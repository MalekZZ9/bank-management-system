#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
class clsCurrenciesListScreen :
    protected clsScreen
{

private:

    static void _PrintRecordLine(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << setw(30) << left << Currency.CountryName();
        cout << "| " << setw(8) << left << Currency.CurrencyCode();
        cout << "| " << setw(45) << left << Currency.CurrencyName();
        cout << "| " << setw(10) << left << Currency.Rate() << endl;
    }

public:

    static void ShowCurrenciesListScreen()
    {
        vector <clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

        clsScreen::_DrawScreenHeader("\t Currencies List Screen", "\t    " + to_string(vCurrencies.size()) + " Currency.");

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << setw(30) << left << "Country";
        cout << "| " << setw(8) << left << "Code";
        cout << "| " << setw(45) << left << "Name";
        cout << "| " << setw(10) << left << "Rate/(1$)";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;


        if (vCurrencies.size() == 0)
            cout << "\t\t\t\tNo Currencies Available In the System!";
        else
            for (clsCurrency& VecCurrency : vCurrencies)
                _PrintRecordLine(VecCurrency);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n" << endl;
    }
};

