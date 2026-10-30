#pragma once
#include "clsScreen.h"
class clsTransferScreen : protected clsScreen
{

private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "___________________\n";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

    static string _ReadAccountNumber(bool IsSender)
    {
        string AccountNumber;
        cout << "\nPlease Enter Account Number to Transfer " << (IsSender ? "From : " : "To : ");
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        return AccountNumber;
    }

    static float ReadAmount(clsBankClient SourceClient)
    {
        float Amount;

        cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidate::ReadPositiveDoubleNumber();

        while (Amount > SourceClient.AccountBalance)
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidate::ReadPositiveDoubleNumber();
        }

        return Amount;
    }

public:

    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\tTransfer Screen");

        clsBankClient SenderClient = clsBankClient::Find(_ReadAccountNumber(true));
        _PrintClient(SenderClient);

        clsBankClient ReceiverClient = clsBankClient::Find(_ReadAccountNumber(false));
        _PrintClient(ReceiverClient);

        float Amount = ReadAmount(SenderClient);

        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        cin >> Answer;

        if (tolower(Answer) == 'y')
        {
            if (SenderClient.Transfer(Amount, ReceiverClient))
            {
                cout << "\nTransfer done successfully\n";
            }
            else
            {
                cout << "\nTransfer Faild \n";
            }

            _PrintClient(SenderClient);
            _PrintClient(ReceiverClient);
        }
    }
};