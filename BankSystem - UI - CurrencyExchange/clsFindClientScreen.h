#pragma once
#include "clsScreen.h"
class clsFindClientScreen :protected clsScreen
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

    static void ShowFindClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
            return;

        clsScreen::_DrawScreenHeader("\tFind Client Screen");

        cout << "Enter Account Number : ";
        string AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Account Number is not found , enter another one : ";
            AccountNumber = clsInputValidate::ReadString();
        }

            clsBankClient Client = clsBankClient::Find(AccountNumber);


            if (!Client.IsEmpty())
            
                cout << "\nClient Found :-)\n";
            
            else
            
                cout << "\nClient Was not Found :-(\n";
            

            _PrintClient(Client);
    }
};

