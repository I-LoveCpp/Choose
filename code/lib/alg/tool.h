#include <iostream>
using namespace std;

template <typename T>
bool Is_LeapYear(T year)
{
	if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) )return true;
	return false;
}

template <typename T>
bool Is_True_Date(T date)
{
	int month_day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int year = date / 10000, month = date % 10000 / 100, day = date % 100;
	
	if(month == 2)
	{
		if(Is_LeapYear(year)) month_day[2] = 29;
	}
	
	if(month >= 13) return false;
	if(month <= 0) return false;
	if(day == 0) return false;
	return day <= month_day[month];
}
