#pragma once
#include "clsScreen.h"
class clsDeleteClientScreen : protected clsScreen
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

	static void ShowDeleteClientScreen()
	{
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
            return;

        clsScreen::_DrawScreenHeader("\tDelete Client Screen");

        cout << "Enter Account Number : ";
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Number is not exist, enter another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        char ConfirmDeletion = 'f';
        cout << "Are you sure you want to delete this clients ? y/n ";
        cin >> ConfirmDeletion;

        if (tolower(ConfirmDeletion) == 'y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted successfully :-)\n";
                _PrintClient(Client);
            }
            else
                cout << "\nError Client Was not Deleted\n";
        }
	}
};

