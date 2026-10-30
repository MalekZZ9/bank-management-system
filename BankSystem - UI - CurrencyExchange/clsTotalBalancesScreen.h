#pragma once
#include "clsScreen.h"
#include "clsUtility.h"
class clsTotalBalancesScreen  : protected clsScreen
{
private:

    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {
        cout << setw(25) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(40) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.AccountBalance << endl;
    }

public:

	static void ShowTotalBalancesScreen()
	{
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        clsScreen::_DrawScreenHeader("\t   Balance List Screen", "\t\t(" + to_string(vClients.size()) + ") Client(s).");
        
        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout << setw(25) << left << "" << "\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else
            for (clsBankClient& VecClient : vClients)
                _PrintClientRecordBalanceLine(VecClient);


        cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
        cout << "__________________________\n" << endl;

        double TotalBalances = clsBankClient::GetTotalBalances();
        cout << setw(8) << left << "" << "\t\t\t\t      Total Balances = " << TotalBalances << endl;
        cout << setw(8) << left << "" << "\t\t  ( " << clsUtility::ConvertNumberToText(TotalBalances) << ")";
    }

};

