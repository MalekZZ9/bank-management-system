#pragma once
#include "clsScreen.h"
class clsAddNewUserScreen : protected clsScreen
{
	static int _ReadUserPermissions()
	{
		char Answer = 'n';

		cout << "Do you want to give full access ? y/n ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			return -1;

		int Permissions = 0;

		cout << "Do you want to give access to :\n\n";

		cout << "Show Clients List? y/n: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::pListClients;

		cout << "Add New Client? y/n: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::pAddNewClient;

		cout << "Delete Client? y/n: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::pDeleteClient;

		cout << "Update Client? y/n: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::pUpdateClient;

		cout << "Find Client? y/n: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::pFindClient;

		cout << "Access Transactions? y/n: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::pTransactions;

		cout << "Manage Users? y/n: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::pManageUsers;

		cout << "Show Login Registers? y/n: ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::pLoginRegister;

		return Permissions;
	}

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter FirstName : ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "Enter LastName : ";
		User.LastName = clsInputValidate::ReadString();

		cout << "Enter Email : ";
		User.Email = clsInputValidate::ReadString();

		cout << "Enter Phone : ";
		User.Phone = clsInputValidate::ReadString();

		cout << "Enter Password : ";
		User.Password = clsInputValidate::ReadString();

		cout << "Enter Permissions : ";
		User.Permissions = _ReadUserPermissions();
	}

	static void _PrintUser(clsUser & User)
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
		cout << "-----------------------------------\n" << endl;
	}

public :

	static void ShowAddNewClientScreen()
	{
		clsScreen::_DrawScreenHeader("\t  Add New User Screen");

		cout << "Enter UserName : ";
		string UserName = clsInputValidate::ReadString();

		while (clsUser::IsUserExist(UserName))
		{
			cout << "UserName is already exist , enter another one : ";
			UserName = clsInputValidate::ReadString();
		}

		clsUser User = clsUser::GetAddNewUserObject(UserName);

		_ReadUserInfo(User);

		clsUser::enSaveResult SaveResults = User.Save();

		switch (SaveResults)
		{
		case clsUser::enSaveResult::svSucceeded:

			cout << "\nUser Added Successfully\n";
			_PrintUser(User);
			break;

		case clsUser::enSaveResult::svFailedEmptyObject:

			cout << "\nError because empty object\n";
			break;

		case clsUser::enSaveResult::svFailedUserNameExist:

			cout << "\nError because UserName Exist\n";
			break;
		}
	}

};