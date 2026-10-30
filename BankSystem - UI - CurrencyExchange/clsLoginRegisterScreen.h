#pragma once
#include "clsScreen.h"

class clsLoginRegisterScreen :
    protected clsScreen
{
private:

    static void PrintLoginRegisterRecordLine(clsUser::stLoginRecord Record)
    {
        cout << setw(8) << left << "" << "| " << setw(35) << left << Record.DateTime;
        cout << "| " << setw(20) << left << Record.UserName;
        cout << "| " << setw(20) << left << Record.Password;
        cout << "| " << setw(10) << left << Record.Permissions << endl;
    }


public:

    static void ShowLoginRegisterScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
            return;

        vector <clsUser::stLoginRecord> vRecords = clsUser::GetLoginRecordsList();

        system("cls");
        _DrawScreenHeader("    Login Register List Screen", "\t    (" + to_string(vRecords.size()) + ") RecordS");


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vRecords.size() == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else
            for (clsUser::stLoginRecord Record : vRecords)
                PrintLoginRegisterRecordLine(Record);


        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};

