#pragma once
#include "clsScreen.h"
class clsDepositScreen : protected clsScreen
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

	static void ShowDepositScreen()
	{
        clsScreen::_DrawScreenHeader("\t   Deposit Screen");


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

        cout << "\nPlease enter deposit amount ? ";
        double DepositAmount = clsInputValidate::ReadPositiveDoubleNumber();

        char DepositConfirmation = 'f';
        cout << "Are you sure you want to perform this transaction ? y/n ";
        cin >> DepositConfirmation;

        if (tolower(DepositConfirmation) == 'y')
        {
            Client.Deposit(DepositAmount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance Is: " << Client.AccountBalance << endl;
        }
        else
            cout << "\nOperation was cancelled.\n";
	}

};

