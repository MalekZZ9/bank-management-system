#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode, UpdateMode, AddNewMode };

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector <string> vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector < clsBankClient > _LoadClientsDataFromFile()
	{
		vector < clsBankClient > vClients;

		fstream BankClientsFile;
		BankClientsFile.open("Clients.txt", ios::in);

		if (BankClientsFile.is_open())
		{
			string Line = "";

			while (getline(BankClientsFile, Line))
				vClients.push_back(_ConvertLineToClientObject(Line));

			BankClientsFile.close();
		}

		return vClients;
	}

	string _ConvertClientToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string Line = "";

		Line += Client.FirstName + Seperator;
		Line += Client.LastName + Seperator;
		Line += Client.Email + Seperator;
		Line += Client.Phone + Seperator;
		Line += Client.AccountNumber() + Seperator;
		Line += Client.PinCode + Seperator;
		Line += to_string(Client.AccountBalance);

		return Line;
	}

	void _SaveCleintsDataToFile(vector < clsBankClient > vClients)
	{

		fstream BankClientsFile;
		BankClientsFile.open("Clients.txt", ios::out);

		if (BankClientsFile.is_open())
		{
			for (clsBankClient& VecClient : vClients)
				if (VecClient.MarkForDelete == false)
					BankClientsFile << _ConvertClientToLine(VecClient) << endl;

			BankClientsFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& VecClient : vClients)
			if (VecClient._AccountNumber == _AccountNumber)
			{
				VecClient = *this;
				break;
			}

		_SaveCleintsDataToFile(vClients);
	}

	void _AddClientLineToFile(string Line)
	{
		fstream BankClientsFile;
		BankClientsFile.open("Clients.txt", ios::out | ios::app);

		if (BankClientsFile.is_open())
		{
			BankClientsFile << Line << endl;

			BankClientsFile.close();
		}
	}

	void _AddNewClient()
	{
		_AddClientLineToFile(_ConvertClientToLine(*this));
	}

	string _PrepearTransferLogRecord(float Amount, clsBankClient& DestinationClient, string UserName, string Seperator = "#//#")
	{
		string TransferLogRecord = "";

		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += this->AccountNumber() + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(this->AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogRecord += UserName;

		return TransferLogRecord;
	}


	void _RegisterTransferLog(float Amount, clsBankClient& DestinationClient, string UserName)
	{
		fstream TransferLogFile;
		TransferLogFile.open("TransferLog.txt", ios::out | ios::app);

		if (TransferLogFile.is_open())
		{
			TransferLogFile << _PrepearTransferLogRecord(Amount , DestinationClient , UserName) << endl;

			TransferLogFile.close();
		}
	}
	

	struct stTransferLogRecord;
	static stTransferLogRecord _ConvertLineToTransferLogReceord(string Line, string Seperator = "#//#")
	{
		stTransferLogRecord TransferLogRecord;
		
		vector <string> vStrings = clsString::Split(Line, Seperator);

		TransferLogRecord.DateTime = vStrings[0];
		TransferLogRecord.SAccNum = vStrings[1];
		TransferLogRecord.RAccNum = vStrings[2];
		TransferLogRecord.Amount = stof(vStrings[3]);
		TransferLogRecord.SBalance= stof(vStrings[4]);
		TransferLogRecord.RBalance = stof(vStrings[5]);
		TransferLogRecord.UserName = vStrings[6];

		return TransferLogRecord;
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone,
		string AccountNumber, string PinCode, double AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	double GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) double AccountBalance;

	//  No UI Related code must be inside core class
	// void Print()
	
	static clsBankClient Find(string AccountNumber)
	{
		vector <clsBankClient> vClients;

		fstream BankClientsFile;
		BankClientsFile.open("Clients.txt", ios::in);

		if (BankClientsFile.is_open())
		{
			string Line = "";

			while (getline(BankClientsFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client._AccountNumber == AccountNumber)
				{
					BankClientsFile.close();
					return Client;
				}

				vClients.push_back(Client);
			}

			BankClientsFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector <clsBankClient> vClients;

		fstream BankClientsFile;
		BankClientsFile.open("Clients.txt", ios::in);

		if (BankClientsFile.is_open())
		{
			string Line = "";

			while (getline(BankClientsFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client._AccountNumber == AccountNumber && Client.PinCode == PinCode)
				{
					BankClientsFile.close();
					return Client;
				}

				vClients.push_back(Client);
			}

			BankClientsFile.close();
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);

		return !(Client.IsEmpty());
	}

	static clsBankClient GetNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	enum enSaveResults { svFailedEmptyObject, svFaildAccountNumberExists, svSucceeded };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:

			if (IsEmpty())
				return enSaveResults::svFailedEmptyObject;

		case enMode::UpdateMode:


			_Update();
			return enSaveResults::svSucceeded;

		case enMode::AddNewMode:

			if (IsClientExist(_AccountNumber))
				return enSaveResults::svFaildAccountNumberExists;
			
			else
			{
				_AddNewClient();

				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}
		}
	}

	bool Delete()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& VecClient : vClients)
			if (VecClient.AccountNumber() == _AccountNumber)
			{
				VecClient.MarkForDelete = true;
				break;
			}

		_SaveCleintsDataToFile(vClients);

		*this = _GetEmptyClientObject();
		return true;
	}
	 
	static vector <clsBankClient > GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		double TotalBalances = 0;
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& VecClient : vClients)
			TotalBalances += VecClient.AccountBalance;

		return TotalBalances;
	}

	void Deposit(double DepositAmount)
	{
		_AccountBalance += DepositAmount;
		Save();
	}

	bool Withdraw(double WithdrawAmount)
	{
		if (WithdrawAmount < _AccountBalance)
		{
			_AccountBalance -= WithdrawAmount;
			Save();
			return true;
		}
		else
			return false;
	}

	bool Transfer(float Amount, clsBankClient& DestinationClient)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Deposit(Amount);

		_RegisterTransferLog(Amount, DestinationClient, CurrentUser.UserName);

		return true;
	}

	struct stTransferLogRecord
	{
		string DateTime;
		string SAccNum;
		string RAccNum;
		float Amount;
		float SBalance;
		float RBalance;
		string UserName;
	};

	static vector < stTransferLogRecord> GetTransferLogList()
	{
		vector < stTransferLogRecord> vTransferRecords;

		fstream TransferLogFile;
		TransferLogFile.open("TransferLog.txt", ios::in);

		if (TransferLogFile.is_open())
		{
			string Line = "";

			while (getline(TransferLogFile, Line))
				vTransferRecords.push_back(_ConvertLineToTransferLogReceord(Line));

			TransferLogFile.close();
		}


		return vTransferRecords;
	}
	

};