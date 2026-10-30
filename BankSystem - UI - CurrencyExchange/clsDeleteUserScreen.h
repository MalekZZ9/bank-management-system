#pragma once
#include "clsScreen.h"
class clsDeleteUserScreen :   protected clsScreen
{
private:

	static void _PrintUser(clsUser& User)
	{
		cout << "\nUser Card :" << endl;
		cout << "-----------------------------------" << endl;
		cout << "First Name  : " << User.FirstName << endl;
		cout << "Last Name   : " << User.LastName << endl;
		cout << "Email       : " << User.Email << endl;
		cout << "Phone       : " << User.Phone << endl;
		cout << "User Name   : " << User.UserName << endl;
		cout << "Password    : " << User.Password << endl;
		cout << "Permissions : " << User.Permissions << endl;
		cout << "-----------------------------------" << endl;
	}

public:

	static void ShowDeleteUserScreen()
	{
		clsScreen::_DrawScreenHeader("\t  Delete User Screen");

		cout << "Enter UserName : ";
		string UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "UserName is not exist , enter another one : ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		_PrintUser(User);

		char DeleteConfirmation = 'n';
		cout << "\nAre you sure you want to delete this user ? y/n: ";
		cin >> DeleteConfirmation;

		if (tolower(DeleteConfirmation) == 'y')
		{
			if (User.Delete())
			{
				cout << "\nUser Deleted Successfully\n";
				_PrintUser(User);
			}
			else
				cout << "\nError User Was not Deleted\n";
		}
	}
};