#pragma once
#include "clsScreen.h"
#include "clsBankClient.h"
class clsAddNewClientScreen : protected clsScreen
{
private:

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName : ";
        Client.FirstName = clsInputValidate::ReadString();

        cout << "\nEnter LastName : ";
        Client.LastName = clsInputValidate::ReadString();

        cout << "\nEnter Email : ";
        Client.Email = clsInputValidate::ReadString();

        cout << "\nEnter Phone : ";
        Client.Phone = clsInputValidate::ReadString();

        cout << "\nEnter PinCode : ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "\nEnter Account Balance : ";
        Client.AccountBalance = clsInputValidate::ReadDoubleNumber();
    }
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

	static void ShowAddNewClientScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
            return;

        clsScreen::_DrawScreenHeader("\t  Add New Client Screen");

        cout << "Enter Account Number : ";
        string AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Number is already used, choose another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::GetNewClientObject(AccountNumber);
        _ReadClientInfo(Client);


        clsBankClient::enSaveResults SaveResult = Client.Save();

        switch (SaveResult)
        {
        case  clsBankClient::enSaveResults::svFailedEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;

        case  clsBankClient::enSaveResults::svFaildAccountNumberExists:
            cout << "\nError account was not saved because Account Number is repeated";
            break;

        case  clsBankClient::enSaveResults::svSucceeded:
            cout << "\nClient Added Successfully !\n";
            _PrintClient(Client);
            break;
        }
	}
};