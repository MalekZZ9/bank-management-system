#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "Global.h"
class clsLoginScreen : protected clsScreen
{
private:



	static bool _Login()
	{
		bool LoginFailed = false;
		short FailedLoginCounter = 0;
		string UserName, Password;

		do
		{

			if (LoginFailed)
			{
				FailedLoginCounter++;

				cout << "\nInvalid UserName/Password !\n";
				cout << "You have " << 3 - FailedLoginCounter << " Trials To Login\n\n";
			}

			if (FailedLoginCounter== 3)
			{
				cout << "\nYou Are Locked after 3 attempts\n";
				return false;
			}

			cout << "Enter UserName : ";
			cin >> UserName;
			
			cout << "Enter Password : ";
			cin >> Password;

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFailed = CurrentUser.IsEmpty();

		} while (LoginFailed);

		CurrentUser.RegisterLogin();

		clsMainScreen::ShowMainMenu();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		clsScreen::_DrawScreenHeader("\t\tLogin Screen");
		return _Login();
	}
};