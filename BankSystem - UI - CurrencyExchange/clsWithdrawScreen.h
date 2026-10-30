#pragma once
#include "clsScreen.h"
class clsWithdrawScreen : protected clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card :";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc.Number  : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

public:

    static void ShowWithdrawScreen()
    {
        clsScreen::_DrawScreenHeader("\t   Withdraw Screen");


        cout << "Enter Account Number : ";
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client with [" << AccountNumber << "] does not exist : ";

            cout << "Enter Account Number : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        cout << "\nPlease enter withdraw amount ? ";
        double WithdrawAmount = clsInputValidate::ReadPositiveDoubleNumber();

        char WithdrawConfirmation = 'f';
        cout << "Are you sure you want to perform this transaction ? y/n ";
        cin >> WithdrawConfirmation;

        if (tolower(WithdrawConfirmation) == 'y')
        {
            if (Client.Withdraw(WithdrawAmount))
            {
                cout << "\nAmount Withdrawed Successfully.\n";
                cout << "\nNew Balance Is: " << Client.AccountBalance << endl;
            }
            else
            {
                cout << "\nCannot withdraw, Insuffecient Balance!\n";
                cout << "\nAmout to withdraw is: " << WithdrawAmount;
                cout << "\nYour Balance is: " << Client.AccountBalance;
            }
        }
        else
            cout << "\nOperation was cancelled.\n";
    }

};