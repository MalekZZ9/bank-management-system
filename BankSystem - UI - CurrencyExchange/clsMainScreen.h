#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeMainScreen.h"
#include "Global.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
private:

    enum _enMainMenueOptions { eShowClientsList = 1 , eAddNewClient , eDeleteClient , 
        eUpdateClient , eFindClient , eTransactions , eManageUsers , eLoginRegister , eCurrencyExchange , eLogout};

    static int _ReadCurrenciesMenuOption()
    {
        cout << left << setw(37) << "" << "Choose What do you want to do ? [1 to 10] : ";
        int Choice = clsInputValidate::ReadIntNumberBetween(1, 10);

        return Choice;
    }

    static void _GoBackToMainMenu()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...";
        system("pause>0");

        ShowMainMenu();
    }

    static void _ShowClientsListScreen()
    {
        clsClientListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenu()
    {
        clsTransactionsScreen::ShowTransactionsMenu();
    }

    static void _ShowManageUsersMenu()
    {
        clsManageUsersScreen::ShowManageUsersScreen();
    }

    static void _ShowLoginRegisterScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowCurrencyExchangeScreen()
    {
        clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMenu();
    }

    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");
    }

    static void _PerformMainMenueOption(_enMainMenueOptions MainMenueOption)
    {

        switch (MainMenueOption)
        {
        case _enMainMenueOptions::eShowClientsList:

            system("cls");
            _ShowClientsListScreen();
            _GoBackToMainMenu();
            break;

        case _enMainMenueOptions::eAddNewClient:

            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenu();
            break;

        case _enMainMenueOptions::eDeleteClient:

            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenu();
            break;

        case _enMainMenueOptions::eUpdateClient:

            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break;

        case _enMainMenueOptions::eFindClient:

            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;

        case _enMainMenueOptions::eTransactions:

            system("cls");
            _ShowTransactionsMenu();
            _GoBackToMainMenu();
            break;

        case _enMainMenueOptions::eManageUsers:

            system("cls");
            _ShowManageUsersMenu();
            _GoBackToMainMenu();
            break;

        case _enMainMenueOptions::eLoginRegister:

            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenu();
            break;

        case _enMainMenueOptions::eCurrencyExchange:

            system("cls");
            _ShowCurrencyExchangeScreen();
            _GoBackToMainMenu();
            break;

        case _enMainMenueOptions::eLogout:

            system("cls");
            _Logout();
            break;

        default:
            break;
        }
    }

public:

    static void ShowMainMenu()
    {
        system("cls");
        clsScreen::_DrawScreenHeader("\t\tMain Screen");

        cout << left  << setw(37)<< "" << "===========================================\n";
        cout << left  << setw(37)<< "" << "\t\t\tMain Menu\n";
        cout << left  << setw(37)<< "" << "===========================================\n";
      
        cout << left  << setw(37)<< "" << "\t[1] Show Client List.\n";
        cout << left  << setw(37)<< "" << "\t[2] Add New Client.\n";
        cout << left  << setw(37)<< "" << "\t[3] Delete Client.\n";
        cout << left  << setw(37)<< "" << "\t[4] Update Client Info.\n";
        cout << left  << setw(37)<< "" << "\t[5] Find Client.\n";
        cout << left  << setw(37)<< "" << "\t[6] Transactions.\n";
        cout << left  << setw(37)<< "" << "\t[7] Manage Users.\n";
        cout << left  << setw(37)<< "" << "\t[8] Login Register.\n";
        cout << left  << setw(37)<< "" << "\t[9] Currency Exchange.\n";
        cout << left  << setw(37)<< "" << "\t[10] Logout.\n";
              
        cout << left  << setw(37)<< "" << "===========================================\n";

        _PerformMainMenueOption((_enMainMenueOptions)_ReadCurrenciesMenuOption());
    }
};