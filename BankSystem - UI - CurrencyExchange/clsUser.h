#pragma once
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtility.h"
#include <vector>
#include <fstream>
#include <string>

class clsUser : public clsPerson
{
private:

    enum enMode { EmptyMode, UpdateMode, AddNewMode };

    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool MarkForDelete = false;
   

    static  clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#")
    {
        vector <string> vStrings = clsString::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vStrings[0], vStrings[1], vStrings[2], vStrings[3], vStrings[4], clsUtility::Decrypt(vStrings[5]), stoi(vStrings[6]));
    }

    static  string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string Line = User.FirstName + Seperator;
        Line += User.LastName + Seperator;
        Line += User.Email + Seperator;
        Line += User.Phone + Seperator;
        Line += User.UserName + Seperator;
        Line += clsUtility::Encrypt(User.Password) + Seperator;
        Line += to_string(User.Permissions);

        return Line;
    }

    static vector <clsUser> _vLoadUsersFromFile()
    {
        vector <clsUser> vUsers;

        fstream UsersFile;
        UsersFile.open("Users.txt", ios::in);

        if (UsersFile.is_open())
        {
            string Line = "";

            while (getline(UsersFile, Line))
                vUsers.push_back(_ConvertLineToUserObject(Line));

            UsersFile.close();
        }

        return vUsers;
    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {
        fstream UsersFile;
        UsersFile.open("Users.txt", ios::out);

        if (UsersFile.is_open())
        {
            for (clsUser& VecUser : vUsers)
                if (VecUser.MarkForDelete == false)
                    UsersFile << _ConvertUserObjectToLine(VecUser) << endl;

            UsersFile.close();
        }
    }

    void _Update()
    {
        vector <clsUser> vUsers = _vLoadUsersFromFile();

        for (clsUser& VecUser : vUsers)
            if (VecUser.UserName == UserName)
            {
                VecUser = *this;
                break;
            }

        _SaveUsersDataToFile(vUsers);
    }

    void _AddUserLineToFile(string Line)
    {
        fstream UsersFile;
        UsersFile.open("Users.txt", ios::out | ios::app);

        if (UsersFile.is_open())
        {
            UsersFile << Line << endl;

            UsersFile.close();
        }
    }

    void _AddNewUser()
    {
        _AddUserLineToFile(_ConvertUserObjectToLine(*this));
    }

    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string LogFileRecord = "";


        LogFileRecord += clsDate::GetSystemDateTimeString() + Seperator;

        LogFileRecord += _UserName + Seperator;
        LogFileRecord += clsUtility::Encrypt(_Password) + Seperator;
        LogFileRecord += to_string(_Permissions);

        return LogFileRecord;
    }

    struct stLoginRecord;
    static stLoginRecord _ConvertLineToLoginRecord(string Line, string Seperator = "#//#")
    {
        stLoginRecord UserRecord;

        vector <string> vStrings = clsString::Split(Line, Seperator);

        UserRecord.DateTime = vStrings[0];
        UserRecord.UserName = vStrings[1];
        UserRecord.Password = clsUtility::Decrypt(vStrings[2]);
        UserRecord.Permissions = stoi(vStrings[3]);

        return UserRecord;
    }

public:

    enum enPermissions {
        pAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64 , pLoginRegister = 128
    };


    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone,
        string UserName, string Password, int Permissions) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    string GetUserName()
    {
        return _UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }
    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }
    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;


    bool IsEmpty()
    {
        return _Mode == EmptyMode;
    }

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line = ""
                ;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);

                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }

        return _GetEmptyUserObject();
    }
    static clsUser Find(string UserName, string Password)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line = ""
                ;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);

                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }

        return _GetEmptyUserObject();
    }

    static bool IsUserExist(string UserName)
    {
        clsUser User = Find(UserName);
        return !User.IsEmpty();
    }

    static enum enSaveResult { svSucceeded, svFailedEmptyObject, svFailedUserNameExist };
    enSaveResult Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:

            if (IsEmpty())
            {
                return svFailedEmptyObject;
            }

        case enMode::UpdateMode:

            _Update();
            return svSucceeded;

        case enMode::AddNewMode:

            if (IsUserExist(UserName))
                return svFailedUserNameExist;
            else
            {
                _AddNewUser();
                _Mode = UpdateMode;
                return svSucceeded;
            }
        }
    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(AddNewMode, "", "", "", "", UserName, "", 0);
    }

    bool Delete()
    {
        vector <clsUser> vUsers = _vLoadUsersFromFile();

        for (clsUser& VecUser : vUsers)
            if (VecUser.UserName == UserName)
            {
                VecUser.MarkForDelete = true;
                break;
            }

        _SaveUsersDataToFile(vUsers);
        *this = _GetEmptyUserObject();
        return true;
    }

    static vector <clsUser> GetUsersList()
    {
        return _vLoadUsersFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->Permissions == enPermissions::pAll)
            return true;

        if ((this->Permissions & Permission) == Permission)
            return true;
        else
            return false;
    }

    void RegisterLogin()
    {
        fstream LogFile;
        LogFile.open("LogFile.txt", ios::out | ios::app);

        if (LogFile.is_open())
        {
            LogFile << _PrepareLogInRecord() << endl;

            LogFile.close();
        }
    }

    struct stLoginRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;
    };

    static vector<stLoginRecord> GetLoginRecordsList()
    {
        vector <stLoginRecord> vRecords;

        fstream LogFile;
        LogFile.open("LogFile.txt", ios::in);

        if (LogFile.is_open())
        {
            string Line;

            while (getline(LogFile, Line))
                vRecords.push_back(_ConvertLineToLoginRecord(Line));

            LogFile.close();
        }

        return vRecords;
    }
};