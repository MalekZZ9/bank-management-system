#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsDate.h"
#include "Global.h"

using namespace std;


class clsScreen
{
protected:

    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________\n\n";
        cout << "\t\t\t\t\t  " << Title << endl;

        if (SubTitle != "")
        {
            cout << "\t\t\t\t\t  " << SubTitle << endl;
        }

        cout << "\t\t\t\t\t______________________________________\n\n";

        cout << "\t\t\t\t\tUser : " << CurrentUser.UserName << endl;
        cout << "\t\t\t\t\tDate : " << clsDate::DateToString(clsDate()) << "\n\n";
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        if (!CurrentUser.CheckAccessPermission(Permission))
        {
            _DrawScreenHeader("Access Denied! Contact Your Admin");
            return false;
        }
        else
            return true;
    }
};
