#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "clsString.h"
using namespace std;

class clsDate
{
private:

	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;

public:

	void SetDay(short Day) { _Day = Day; }
	short GetDay() { return _Day; }
	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month) { _Month = Month; }
	short GetMonth() { return _Month; }
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year) { _Year = Year; }
	short GetYear() { return _Year; }
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	clsDate()
	{
		time_t Date = time(0);
		tm* LocalDate = localtime(&Date);

		_Day = LocalDate->tm_mday;
		_Month = LocalDate->tm_mon + 1;
		_Year = LocalDate->tm_year + 1900;
	}
	clsDate(string StrDate)
	{
		vector <string> vStrings = clsString::Split(StrDate, "/");

		_Day = stoi(vStrings[0]);
		_Month = stoi(vStrings[1]);
		_Year = stoi(vStrings[2]);
	}
	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(short DayOrderInYear, short Year)
	{
		clsDate Date = GetDateFromDayOrderInYear(DayOrderInYear, Year);

		_Day = Date.Day;
		_Month = Date.Month;
		_Year = Date.Year;
	}



	static bool IsLeapYear(short Year)
	{
		return (Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0));
	}
	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}



	static short GetNumberOfDaysInYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}
	short GetNumberOfDaysInYear()
	{
		return GetNumberOfDaysInYear(_Year);
	}

	static short GetNumberOfHoursInYear(short Year)
	{
		return GetNumberOfDaysInYear(Year) * 24;
	}
	short GetNumberOfHoursInYear()
	{
		return GetNumberOfHoursInYear(_Year);
	}

	static int GetNumberOfMinutesInYear(short Year)
	{
		return GetNumberOfHoursInYear(Year) * 60;
	}
	int GetNumberOfMinutesInYear()
	{
		return GetNumberOfMinutesInYear(_Year);
	}

	static int GetNumberOfSecondsInYear(short Year)
	{
		return GetNumberOfMinutesInYear(Year) * 60;
	}
	int GetNumberOfSecondsInYear()
	{
		return GetNumberOfSecondsInYear(_Year);
	}


	static short GetNumberOfDaysInMonth(short Month, short Year)
	{
		short MonthsArr[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (Month == 2 ? (IsLeapYear(Year) ? 29 : 28) : MonthsArr[Month - 1]);
	}
	short GetNumberOfDaysInMonth()
	{
		return GetNumberOfDaysInMonth(_Month, _Year);
	}

	static short GetNumberOfHoursInMonth(short Month, short Year)
	{
		return GetNumberOfDaysInMonth(Month, Year) * 24;
	}
	short GetNumberOfHoursInMonth()
	{
		return GetNumberOfHoursInMonth(_Month, _Year);
	}

	static int GetNumberOfMinutesInMonth(short Month, short Year)
	{
		return GetNumberOfHoursInMonth(Month, Year) * 60;
	}
	int GetNumberOfMinutesInMonth()
	{
		return GetNumberOfMinutesInMonth(_Month, _Year);
	}

	static int GetNumberOfSecondsInMonth(short Month, short Year)
	{
		return GetNumberOfMinutesInMonth(Month, Year) * 60;
	}
	int GetNumberOfSecondsInMonth()
	{
		return GetNumberOfSecondsInMonth(_Month, _Year);
	}



	static short GetDayOrderInWeek(short Day, short Month, short Year)
	{
		short a = (14 - Month) / 12;
		short y = Year - a;
		short m = Month + 12 * a - 2;

		return (Day + y + y / 4 - y / 100 + y / 400 + 31 * m / 12) % 7;
	}
	short GetDayOrderInWeek()
	{
		return GetDayOrderInWeek(_Day, _Month, _Year);
	}

	static string GetDayName(short DayOrderInWeek)
	{
		string DaysArr[] = { "Sun" , "Mon" , "Tue" , "Wed" , "Thu" , "Fri" , "Sat" };

		return DaysArr[DayOrderInWeek];
	}
	string GetDayName()
	{
		return GetDayName(GetDayOrderInWeek(_Day, _Month, _Year));
	}



	static string GetMonthName(short Month)
	{
		string MonthsArr[] = { "Jan" , "Feb" , "Mar" , "Apr" , "May" ,"Jun"
			, "Jul" , "Aug" , "Sep" , "Oct" , "Nov" , "Dec" };

		return MonthsArr[Month - 1];
	}
	string GetMonthName()
	{
		return GetMonthName(_Month);
	}

	static void PrintMonthCalender(short Month, short Year)
	{
		printf("\n  _______________%s_______________\n", GetMonthName(Month).c_str());
		printf("\n  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

		short DayOrderInWeek = GetDayOrderInWeek(1, Month, Year);
		int i;
		for (i = 0; i < DayOrderInWeek; i++)
			cout << "     ";

		short NumberOfDaysInMonth = GetNumberOfDaysInMonth(Month, Year);
		for (int j = 1; j <= NumberOfDaysInMonth; j++)
		{
			cout << setw(5) << j;

			if (++i == 7)
			{
				i = 0;
				cout << endl;
			}
		}

		printf("\n  _________________________________\n");
	}
	void PrintMonthCalender()
	{
		PrintMonthCalender(_Month, _Year);
	}

	static void PrintYearCalender(short Year)
	{
		printf("\n  _________________________________\n");
		printf("\n           Calendar - %d", Year);
		printf("\n  _________________________________\n\n");

		for (int i = 1; i <= 12; i++)
			PrintMonthCalender(i, Year);
	}
	void PrintYearCalender()
	{
		PrintYearCalender(_Year);
	}



	static short GetNumberOfDaysFromTheBeginningOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;

		for (int i = 1; i < Month; i++)
			TotalDays += GetNumberOfDaysInMonth(i, Year);

		TotalDays += Day;

		return TotalDays;
	}
	short GetNumberOfDaysFromTheBeginningOfTheYear()
	{
		return GetNumberOfDaysFromTheBeginningOfTheYear(_Day, _Month, _Year);
	}

	static clsDate GetDateFromDayOrderInYear(short DayOrderInYear, short Year)
	{
		clsDate Date;

		Date.Day = DayOrderInYear;
		Date.Month = 1;
		Date.Year = Year;

		short RemainningDays = DayOrderInYear;
		short NumberOfDaysInMonth = 0;

		while (true)
		{
			NumberOfDaysInMonth = GetNumberOfDaysInMonth(Date.Month, Date.Year);

			if (RemainningDays > NumberOfDaysInMonth)
			{
				RemainningDays -= NumberOfDaysInMonth;
				Date.Month++;

				if (Date.Month == 13)
				{
					Date.Year++;
					Date.Month = 1;
				}
			}
			else
			{
				Date.Day = RemainningDays;
				break;
			}
		}

		return Date;
	}



	static clsDate AddDaysToDate(short AddedDays, clsDate Date)
	{
		short TotalDays = GetNumberOfDaysFromTheBeginningOfTheYear(Date.Day, Date.Month, Date.Year) + AddedDays;

		return GetDateFromDayOrderInYear(TotalDays, Date.Year);
	}
	clsDate AddDaysToDate(short AddedDays)
	{
		return AddDaysToDate(AddedDays, *this);
	}



	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return ((Date1.Year < Date2.Year) ||
			((Date1.Year == Date2.Year) && (Date1.Month < Date2.Month)) ||
			((Date1.Year == Date2.Year) && (Date1.Month == Date2.Month) && (Date1.Day < Date2.Day)));
	}
	bool IsDateBeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day == Date2.Day);
	}
	bool IsDateEqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
	}
	bool IsDate1AfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}



	static bool IsLastDayInMonth(short Day, short Month, short Year)
	{
		return Day == GetNumberOfDaysInMonth(Month, Year);
	}
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(_Day, _Month, _Year);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return Month == 12;
	}
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}

	static clsDate IncreaseDateByOneDay(clsDate Date)
	{
		if (!IsLastDayInMonth(Date.Day, Date.Month, Date.Year))
		{
			Date.Day++;
		}
		else
		{
			if (!IsLastMonthInYear(Date.Month))
			{
				Date.Day = 1;
				Date.Month++;
			}
			else
			{
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
		}

		return Date;
	}
	void IncreaseDateByOneDay()
	{
		IncreaseDateByOneDay(*this);
	}



	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;

		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;
	}
	void SwapDates(clsDate& Date2)
	{
		SwapDates(*this, Date2);
	}

	static short GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		short Days = 0;
		short FlipFlag = 1;

		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			FlipFlag = -1;
			SwapDates(Date1, Date2);
		}

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			Date1 = IncreaseDateByOneDay(Date1);
			Days++;
		}

		return IncludeEndDay ? (++Days) * FlipFlag : Days * FlipFlag;
	}
	short GetDifferenceInDays(clsDate Date2)
	{
		return GetDifferenceInDays(*this, Date2);
	}



	static clsDate GetSystemDate()
	{
		clsDate Date;

		time_t Now = time(0);
		tm* LocalDate = localtime(&Now);

		Date.Day = LocalDate->tm_mday;
		Date.Month = LocalDate->tm_mon + 1;
		Date.Year = LocalDate->tm_year + 1900;

		return Date;
	}

	static int GetAgeInDays(clsDate DateOfBirth)
	{
		clsDate SysDate = GetSystemDate();

		return GetDifferenceInDays(DateOfBirth, SysDate);
	}



	static clsDate IncreaseDateByXDays(short Days, clsDate& Date)
	{
		for (int i = 1; i <= Days; i++)
			Date = IncreaseDateByOneDay(Date);

		return Date;
	}
	void IncreaseDateByXDays(short Days)
	{
		IncreaseDateByXDays(Days, *this);
	}

	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		for (int i = 1; i <= 7; i++)
			Date = IncreaseDateByOneDay(Date);

		return Date;
	}
	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeeks(short Weeks, clsDate& Date)
	{
		for (int i = 1; i <= Weeks; i++)
			Date = IncreaseDateByOneWeek(Date);

		return Date;
	}
	void IncreaseDateByXWeeks(short Weeks)
	{
		IncreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (IsLastMonthInYear(Date.Month))
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}

		short NumberOfDaysInCurrentMonth = GetNumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > NumberOfDaysInCurrentMonth)
			Date.Day = NumberOfDaysInCurrentMonth;

		return Date;
	}
	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonths(short Months, clsDate& Date)
	{
		for (int i = 1; i <= Months; i++)
			Date = IncreaseDateByOneMonth(Date);

		return Date;
	}
	void IncreaseDateByXMonths(short Months)
	{
		IncreaseDateByXMonths(Months, *this);
	}

	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date.Year++;

		return Date;
	}
	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYears(short Years, clsDate& Date)
	{
		for (int i = 1; i <= Years; i++)
			Date = IncreaseDateByOneYear(Date);

		return Date;
	}
	void IncreaseDateByXYears(short Years)
	{
		IncreaseDateByXYears(Years, *this);
	}

	static clsDate IncreaseDateByXYearsFaster(short Years, clsDate& Date)
	{
		Date.Year += Years;

		return Date;
	}
	void IncreaseDateByXYearsFaster(short Years)
	{
		IncreaseDateByXYearsFaster(Years, *this);
	}

	static clsDate IncreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year += 10;

		return Date;
	}
	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecades(short Decades, clsDate& Date)
	{
		for (int i = 1; i <= Decades; i++)
			Date = IncreaseDateByOneDecade(Date);

		return Date;
	}
	void IncreaseDateByXDecades(short Decades)
	{
		IncreaseDateByXDecades(Decades, *this);
	}

	static clsDate IncreaseDateByXDecadesFaster(short Decades, clsDate& Date)
	{
		Date.Year += Decades * 10;

		return Date;
	}
	void IncreaseDateByXDecadesFaster(short Decades)
	{
		IncreaseDateByXDecadesFaster(Decades, *this);
	}

	static clsDate IncreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year += 100;

		return Date;
	}
	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year += 1000;

		return Date;
	}
	void IncreaseDateByOneMillennium()
	{
		IncreaseDateByOneMillennium(*this);
	}



	static clsDate DecreaseDateByOneDay(clsDate& Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Day = 31;
				Date.Month = 12;
				Date.Year--;
			}
			else
			{
				Date.Month--;
				Date.Day = GetNumberOfDaysInMonth(Date.Month, Date.Year);
			}
		}
		else
		{
			Date.Day--;
		}

		return Date;
	}
	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(short Days, clsDate& Date)
	{
		for (int i = 1; i <= Days; i++)
			Date = DecreaseDateByOneDay(Date);

		return Date;
	}
	void DecreaseDateByXDays(short Days)
	{
		DecreaseDateByXDays(Days, *this);
	}

	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		for (int i = 1; i <= 7; i++)
			Date = DecreaseDateByOneDay(Date);

		return Date;
	}
	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(short Weeks, clsDate& Date)
	{
		for (int i = 1; i <= Weeks; i++)
			Date = DecreaseDateByOneWeek(Date);
	}
	void DecreaseDateByXWeeks(short Weeks)
	{
		DecreaseDateByXWeeks(Weeks, *this);
	}

	static clsDate DecreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month != 1)
		{
			Date.Month--;
		}
		else
		{
			Date.Month = 12;
			Date.Year--;
		}

		short NumberOfDaysInCurrentMonth = GetNumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > NumberOfDaysInCurrentMonth)
			Date.Day = NumberOfDaysInCurrentMonth;

		return Date;
	}
	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(short Months, clsDate& Date)
	{
		for (int i = 1; i <= Months; i++)
			Date = DecreaseDateByOneMonth(Date);
	}
	void DecreaseDateByXMonths(short Months)
	{
		DecreaseDateByXMonths(Months, *this);
	}

	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{
		Date.Year--;

		return Date;
	}
	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(short Years, clsDate& Date)
	{
		for (int i = 1; i <= Years; i++)
			Date = DecreaseDateByOneYear(Date);

		return Date;
	}
	void  DecreaseDateByXYears(short Years)
	{
		DecreaseDateByXYears(Years, *this);
	}

	static clsDate DecreaseDateByXYearsFaster(short Years, clsDate& Date)
	{
		Date.Year -= Years;

		return Date;
	}
	void  DecreaseDateByXYearsFaster(short Years)
	{
		DecreaseDateByXYearsFaster(Years, *this);
	}

	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		Date.Year -= 10;

		return Date;
	}
	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(short Decades, clsDate& Date)
	{
		for (int i = 1; i <= Decades; i++)
			Date = DecreaseDateByOneDecade(Date);

		return Date;
	}
	void DecreaseDateByXDecades(short Decades)
	{
		DecreaseDateByXDecades(Decades, *this);
	}

	static clsDate DecreaseDateByXDecadesFaster(short Decades, clsDate& Date)
	{
		Date.Year -= Decades * 10;

		return Date;
	}
	void DecreaseDateByXDecadesFaster(short Decades)
	{
		DecreaseDateByXDecadesFaster(Decades, *this);
	}

	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		Date.Year -= 100;

		return Date;
	}
	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		Date.Year -= 1000;

		return Date;
	}
	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}



	static bool IsEndOfWeekDay(clsDate Date)
	{
		return GetDayOrderInWeek(Date.Day, Date.Month, Date.Year) == 6;
	}
	bool IsEndOfWeekDay()
	{
		return IsEndOfWeekDay(*this);
	}

	static bool IsWeekEndDay(clsDate Date)
	{
		short DayOrderInWeek = GetDayOrderInWeek(Date.Day, Date.Month, Date.Year);

		return DayOrderInWeek == 5 || DayOrderInWeek == 6;
	}
	bool IsWeekEndDay()
	{
		return IsWeekEndDay(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEndDay(Date);
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short GetNumberOfDaysUntilEndOfWeekDay(clsDate Date)
	{
		return 6 - GetDayOrderInWeek(Date.Day, Date.Month, Date.Year);
	}
	short GetNumberOfDaysUntilEndOfWeekDay()
	{
		return GetNumberOfDaysUntilEndOfWeekDay(*this);
	}

	static short GetNumberOfDaysUntilEndOfMonthDay(clsDate Date)
	{
		return GetNumberOfDaysInMonth(Date.Month, Date.Year) - Date.Day;

		/*
		   OR :
			clsDate EndOfMontDate;
			EndOfMontDate.Day = NumberOfDaysInAMonth(Date1.Month, Date1.Year);
			EndOfMontDate.Month = Date1.Month;
			EndOfMontDate.Year = Date1.Year;

			return GetDifferenceInDays(Date1, EndOfMontDate, true);
		*/
	}
	short GetNumberOfDaysUntilEndOfMonthDay()
	{
		return GetNumberOfDaysUntilEndOfMonthDay(*this);
	}

	static short GetNumberOfDaysUntilEndOfYearDay(clsDate Date)
	{
		return GetNumberOfDaysInYear(Date.Year) - GetNumberOfDaysFromTheBeginningOfTheYear(Date.Day, Date.Month, Date.Year);

		/*
			 OR :
			clsDate EndOfYearDate;
			EndOfYearDate.Day = 31;
			EndOfYearDate.Month = 12;
			EndOfYearDate.Year = Date1.Year;

			return GetDifferenceInDays(Date1, EndOfYearDate, true);
		*/
	}
	short GetNumberOfDaysUntilEndOfYearDay()
	{
		return GetNumberOfDaysUntilEndOfYearDay(*this);
	}


	static short GetVacationDays(clsDate Date1, clsDate Date2)
	{
		short VacationDays = 0;

		while (IsDate1BeforeDate2(Date1, Date2))
		{
			if (IsBusinessDay(Date1))
				VacationDays++;

			Date1 = IncreaseDateByOneDay(Date1);;
		}

		return VacationDays;
	}

	static clsDate GetVacationReturnDate(clsDate Date, short VacationDays)
	{
		while (VacationDays != 0)
		{
			if (IsBusinessDay(Date))
				VacationDays--;

			Date = IncreaseDateByOneDay(Date);
		}

		return Date;

		/*
			OR :

		   short WeekEndCounter = 0;

		   //in case the data  is weekend keep adding one day util you reach business day
		   //we get rid of all weekends before the first business day
		   while (IsWeekEnd(DateFrom))
		   {
			   DateFrom = IncreaseDateByOneDay(DateFrom);
		   }

		   //here we increase the vacation dates to add all weekends to it.

		   for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
		   {

			   if (IsWeekEnd(DateFrom))
				   WeekEndCounter++;

			   DateFrom = IncreaseDateByOneDay(DateFrom);
		   }

		   //in case the return date is week end keep adding one day util you reach business day
		   while (IsWeekEnd(DateFrom))
		   {
			   DateFrom = IncreaseDateByOneDay(DateFrom);
		   }

		   return DateFrom;
		*/
	}



	enum enCompareDates { Before = -1, Equal = 0, After = 1 };
	static enCompareDates CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enCompareDates::Before;

		if (IsDate1EqualDate2(Date1, Date2))
			return enCompareDates::Equal;

		return enCompareDates::After;
	}
	enCompareDates CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}



	static bool IsValidDate(clsDate Date)
	{
		if (Date.Year < 0)
			return false;

		if (Date.Month < 1 || Date.Month > 12)
			return false;

		if (Date.Day < 1 || Date.Day >= GetNumberOfDaysInMonth(Date.Month, Date.Year))
			return false;

		return true;
	}
	bool IsValid()
	{
		return IsValidDate(*this);
	}



	static string DateToString(clsDate Date)
	{
		return  to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}
	string DateToString()
	{
		return  DateToString(*this);
	}

	static void Print(clsDate Date)
	{
		printf("\n%d/%d/%d\n", Date.Day, Date.Month, Date.Year); // OR cout << DateToString(Date) << endl;
	}
	void Print()
	{
		Print(*this);
	}



	static string FormateDate(clsDate Date, string DateFormate = "dd/mm/yyyy")
	{
		string FromattedDateString = "";

		FromattedDateString = clsString::ReplaceWord(DateFormate, "dd", to_string(Date.Day));
		FromattedDateString = clsString::ReplaceWord(FromattedDateString, "mm", to_string(Date.Month));
		FromattedDateString = clsString::ReplaceWord(FromattedDateString, "yyyy", to_string(Date.Year));

		return FromattedDateString;
	}
	string FormateDate(string DateFormate = "dd/mm/yyyy")
	{
		cout << FormateDate(*this, DateFormate) << endl;
	}

	static string GetSystemDateTimeString()
	{
		//system date/time string
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));
	}

};