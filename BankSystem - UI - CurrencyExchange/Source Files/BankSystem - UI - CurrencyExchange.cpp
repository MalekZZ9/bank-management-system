#include <iostream>
#include "../Header Files/PrimaryMenus/clsMainScreen.h"
#include "../Header Files/PrimaryMenus/clsLoginScreen.h"
#include "../Header Files/Global.h"
using namespace std;


int main()
{
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
            break;
    }

    system("pause>0");
    return 0;
}