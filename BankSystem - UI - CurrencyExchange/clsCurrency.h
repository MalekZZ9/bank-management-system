#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"
using namespace std;


class clsCurrency
{
private:

    enum enMode { EmptyMode, UpdateMode };
    enMode _Mode;
    string _CountryName;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;

    static clsCurrency _ConvertLinetoCurrencyObject(string Line, string Seperator = "#//#")
    {
        vector <string> vStrings = clsString::Split(Line, Seperator);

        return clsCurrency(UpdateMode, vStrings[0], vStrings[1], vStrings[2], stof(vStrings[3]));
    }

    static vector <clsCurrency> _LoadCurrencysDataFromFile()
    {
        vector <clsCurrency> vCurrencies;

        fstream CurrenciesFile;
        CurrenciesFile.open("Currencies.txt", ios::in);

        if (CurrenciesFile.is_open())
        {
            string Line = "";

            while (getline(CurrenciesFile, Line))
                vCurrencies.push_back(_ConvertLinetoCurrencyObject(Line));

            CurrenciesFile.close();
        }

        return vCurrencies;
    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

    static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
    {
        string Line = "";

        Line += Currency.CountryName() + Seperator;
        Line += Currency.CurrencyCode() + Seperator;
        Line += Currency.CurrencyName() + Seperator;
        Line += to_string(Currency.Rate());

        return Line;
    }

    static void _SaveCurrenciesInFile(vector <clsCurrency> vCurrencies)
    {
        fstream CurrenciesFile;
        CurrenciesFile.open("Currencies.txt", ios::out);


        if (CurrenciesFile.is_open())
            for (clsCurrency& VecCurrency : vCurrencies)
                CurrenciesFile << _ConvertCurrencyObjectToLine(VecCurrency) << endl;

        CurrenciesFile.close();
    }

    void _Update()
    {
        vector <clsCurrency> vCurrencies = _LoadCurrencysDataFromFile();

        for (clsCurrency& VecCurrency : vCurrencies)
            if (VecCurrency.CurrencyCode() == _CurrencyCode)
            {
                VecCurrency = *this;
                break;
            }

        _SaveCurrenciesInFile(vCurrencies);
    }

public:

    clsCurrency(enMode Mode, string CountryName, string CurrencyCode,
        string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _CountryName = CountryName;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }

    bool IsEmpty()
    {
        return _Mode == enMode::EmptyMode;
    }
    string CountryName()
    {
        return _CountryName;
    }
    string CurrencyCode()
    {
        return _CurrencyCode;
    }
    string CurrencyName()
    {
        return _CurrencyName;
    }
    float Rate()
    {
        return _Rate;
    }

    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }

    static clsCurrency FindByCurrencyCode(string CurrencyCode)
    {

        CurrencyCode = clsString::UpperAllString(CurrencyCode);

        fstream CurrenciesFile;
        CurrenciesFile.open("Currencies.txt", ios::in);

        if (CurrenciesFile.is_open())
        {
            string Line = "";
            while (getline(CurrenciesFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (Currency.CurrencyCode() == CurrencyCode)
                {
                    CurrenciesFile.close();
                    return Currency;
                }
            }

            CurrenciesFile.close();
        }

        return _GetEmptyCurrencyObject();
    }

    static clsCurrency FindByCountryName(string CountryName)
    {
        CountryName = clsString::UpperAllString(CountryName);

        fstream CurrenciesFile;
        CurrenciesFile.open("Currencies.txt", ios::in);//read Mode

        if (CurrenciesFile.is_open())
        {
            string Line;
            while (getline(CurrenciesFile, Line))
            {
                clsCurrency Currency = _ConvertLinetoCurrencyObject(Line);
                if (clsString::UpperAllString(Currency.CountryName()) == CountryName)
                {
                    CurrenciesFile.close();
                    return Currency;
                }
            }

            CurrenciesFile.close();
        }

        return _GetEmptyCurrencyObject();
    }

    static bool IsCurrencyExist(string CurrencyCode)
    {
        clsCurrency C1 = clsCurrency::FindByCurrencyCode(CurrencyCode);
        return (!C1.IsEmpty());
    }

    static vector <clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrencysDataFromFile();
    }

    float ConvertToUSD(float Amount)
    {
        return Amount / _Rate;
    }

    float ConvertToOtherCurrency(float Amount, clsCurrency Currency2)
    {
        float AmountInUSD = this->ConvertToUSD(Amount);

        if (Currency2.CurrencyCode() == "USD")
            return AmountInUSD;
        else
            return AmountInUSD * Currency2.Rate();
    }

};