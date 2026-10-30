#pragma once
#include "clsScreen.h"
class clsFindUserScreen : protected clsScreen
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

	static void ShowFindUserScreen()
	{
		clsScreen::_DrawScreenHeader("\t  Find User Screen");

		cout << "Enter UserName : ";
		string UserName = clsInputValidate::ReadString();

		while (!clsUser::IsUserExist(UserName))
		{
			cout << "UserName is not exist , enter another one : ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::Find(UserName);

		if (!User.IsEmpty())
		{
			cout << "\nUser Found :-)\n";
		}
		else
		{
			cout << "\nUser Was not Found :-(\n";
		}

		_PrintUser(User);
	}
};