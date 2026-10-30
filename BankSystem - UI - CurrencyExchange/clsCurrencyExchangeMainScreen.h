#pragma once
#include "clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyExchangeScreen.h"
class clsCurrencyExchangeMainScreen : protected clsScreen
{
private:

    enum enCurrenciesOptions {
        eListCurrencies = 1, eFindCurrency, eUpdateCurrencyRate,
        eCurrencyCalculator, eCurrenciesMenu
    };

    static int _ReadCurrenciesMenuOption()
    {
        cout << left << setw(37) << "" << "Choose What do you want to do ? [1 to 5] : ";
        int Choice = clsInputValidate::ReadIntNumberBetween(1, 5);

        return Choice;
    }

    static void _GoBackToCurrenciesMenu()
    {
        cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        ShowCurrencyExchangeMenu();
    }

    static void _ShowListCurrenciesScreen()
    {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }

    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
    }

    static void _PerfromCurrenciesMenuOptions(enCurrenciesOptions CurrenciesOption)
    {
        switch (CurrenciesOption)
        {
        case enCurrenciesOptions::eListCurrencies:

            system("cls");
            _ShowListCurrenciesScreen();
            _GoBackToCurrenciesMenu();
            break;

        case enCurrenciesOptions::eFindCurrency:

            system("cls");
            _ShowFindCurrencyScreen();
            _GoBackToCurrenciesMenu();
            break;

        case enCurrenciesOptions::eUpdateCurrencyRate:

            system("cls");
            _ShowUpdateRateScreen();
            _GoBackToCurrenciesMenu();
            break;

        case enCurrenciesOptions::eCurrencyCalculator:

            system("cls");
            _ShowCurrencyCalculatorScreen();
            _GoBackToCurrenciesMenu();
            break;

        case enCurrenciesOptions::eCurrenciesMenu:
  
            break;
        }
    }

public:

    static void ShowCurrencyExchangeMenu()
    {        
        system("cls");
        clsScreen::_DrawScreenHeader("   Currency Exchange Menu Screen");
    
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Exhange Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator.\n";
        cout << setw(37) << left << "" << "\t[5] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromCurrenciesMenuOptions((enCurrenciesOptions)_ReadCurrenciesMenuOption());
    }
};