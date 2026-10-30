# Bank Management System

A menu-driven C++ console application developed in Visual Studio as a learning project. It combines banking operations, user administration, and currency conversion using object-oriented design and local text-file storage.

## Features

- **Client management:** add, list, search, update, and delete client records.
- **Banking operations:** deposits, withdrawals, account-to-account transfers, and total balance reporting.
- **User management:** add, list, search, update, and delete application users.
- **Access control:** username/password login, a three-attempt login limit, and permissions stored as bit flags.
- **Activity history:** timestamped login records and transfer logs.
- **Currency exchange:** list currencies, search by country or currency code, edit stored rates, and convert between currencies through USD.
- **Reusable utilities:** input validation, string manipulation, date handling, and console formatting.

## Technology and design

- C++ and the C++ Standard Library (`vector`, `string`, and file streams).
- Microsoft Visual Studio solution and MSVC compiler.
- Inheritance and encapsulation: `clsBankClient` and `clsUser` extend `clsPerson`.
- Separate classes for domain models and console screens.
- Delimited text files for persistence; no database or external API is required.

## Build and run

### Requirements

- Windows.
- Visual Studio 2022 with **Desktop development with C++**, the **MSVC v143** toolset, and a Windows 10/11 SDK.
- A newer Visual Studio version can also be used by retargeting the project to an installed MSVC toolset.

The code uses Microsoft's `__declspec(property)` extension and Windows console commands.

### Setup

1. Clone the repository and open `BankSystem - UI - CurrencyExchange.sln`.
2. Before the first run, copy the fictional example data into the project directory. From PowerShell in the repository root:

   ```powershell
   $projectDir = '.\BankSystem - UI - CurrencyExchange'
   Copy-Item '.\examples\Users.txt' -Destination $projectDir
   Copy-Item '.\examples\Clients.txt' -Destination $projectDir
   ```

   This replaces existing files with the same names; use it for a fresh clone or back up existing data first.

3. Select **Debug | x64**, then choose **Build > Build Solution**.
4. In the project properties under **Configuration Properties > Debugging**, set **Working Directory** to `$(ProjectDir)`.
5. Run with **Ctrl+F5**. Sign in with username **`admin`** and password **`demo123`**. This is a public demonstration account with all permissions.

The working directory must contain `Users.txt`, `Clients.txt`, and the included `Currencies.txt`. Login and transfer history files are created when needed. Local user/client data and logs are excluded by `.gitignore`; the `examples` directory contains only fictional data.

For a command-line build, run this from a Visual Studio Developer PowerShell in the repository root:

```powershell
msbuild '.\BankSystem - UI - CurrencyExchange.sln' /p:Configuration=Debug /p:Platform=x64
```

## Project structure

| Files | Purpose |
| --- | --- |
| `BankSystem - UI - CurrencyExchange.cpp` | Entry point and login loop |
| `clsPerson.h`, `clsBankClient.h`, `clsUser.h`, `clsCurrency.h` | Domain models and file persistence |
| `cls*Screen.h` | Console menus and workflows |
| `clsString.h`, `clsDate.h`, `clsInputValidate.h`, `clsUtility.h` | Shared utility classes |
| `Currencies.txt` | Stored currency data and example exchange rates |
| `examples/` | Fictional initial client and user records |

The source files and `Currencies.txt` are inside the `BankSystem - UI - CurrencyExchange` project directory.

## Project scope

This is an educational banking simulation. Exchange rates are stored locally and updated manually. Passwords use a reversible character-shift encoding, and account data is stored in text files. Use fictional data for demonstrations; the application is not intended for real banking operations.

## CV description

**Bank Management System | C++, Visual Studio**

Developed a console banking application using object-oriented C++, supporting client and user management, deposits, withdrawals, fund transfers, and currency conversion. Implemented permission-based access control, login and transfer logging, input validation, and file-based data persistence.
