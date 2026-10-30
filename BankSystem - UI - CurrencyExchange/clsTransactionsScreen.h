#pragma once
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionsScreen : protected clsScreen
{
private:

    enum _enTransactionsMenueOptions { eDeposit = 1, eWithdraw, eTotalBalances,eTransfer, eTransferLog, eCurrenciesMenu };

    static int _ReadTransactionsMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6] ";
        int Choice = clsInputValidate::ReadIntNumberBetween(1, 6);

        return Choice;
    }

    static void _GoBackToTransactionsMenu()
    {
        cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        ShowTransactionsMenu();
    }

    static void _ShowDepositScreen()
    {
        // cout << "Deposit code will be here (adding money to an account).\n";
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }

    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogScreen()
    {
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _PerfromTransactionsMenueOptions(_enTransactionsMenueOptions TransactionsMenueOption)
    {
        switch (TransactionsMenueOption)
        {
        case _enTransactionsMenueOptions::eDeposit:
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenu();
            break;

        case _enTransactionsMenueOptions::eWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenu();
            break;

        case _enTransactionsMenueOptions::eTotalBalances:
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenu();
            break;

        case _enTransactionsMenueOptions::eTransfer:
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenu();
            break;

        case _enTransactionsMenueOptions::eTransferLog:
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenu();
            break;


        case _enTransactionsMenueOptions::eCurrenciesMenu:

            //do nothing here the main screen will handle it :-) ;
            break;
        }
    }

public:

    static void ShowTransactionsMenu()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pTransactions))
            return;

        system("cls");
        clsScreen::_DrawScreenHeader("\tTransactions Screen");


        cout << left << setw(37) << "" << "===========================================\n";
        cout << left << setw(37) << "" << "\t\t\tTransactions Menu\n";
        cout << left << setw(37) << "" << "===========================================\n";

        cout << left << setw(37) << "" << "\t[1] Deposit.\n";
        cout << left << setw(37) << "" << "\t[2] Withdraw.\n";
        cout << left << setw(37) << "" << "\t[3] Total Balances.\n";
        cout << left << setw(37) << "" << "\t[4] Transfer.\n";
        cout << left << setw(37) << "" << "\t[5] Transfer Log.\n";
        cout << left << setw(37) << "" << "\t[6] Main Menu.\n";
        cout << left << setw(37) << "" << "===========================================\n";

        _PerfromTransactionsMenueOptions((_enTransactionsMenueOptions)_ReadTransactionsMenueOption());
    }
};