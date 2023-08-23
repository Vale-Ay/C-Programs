#include"calendar.h"
#include <stdlib.h>
#include <stdio.h>

/* This file contains count function and 
some relevant functions
*/

int count(int fromMonth, int fromDay, int fromYear, int toMonth, int toDay, int toYear) 
{
  const int days[] = {0, 30};

	if(toDay < fromDay)
	{
		if(toMonth == 3)
		{
			if(isLeapYear(toYear))
			{
			  toDay += 29; 
			}
			else
			{
			  toDay += 28;
			}
    }
	  else if(toMonth == 12 || toMonth ==10 || toMonth == 5 || toMonth == 7)
	  {
		  toDay += 30;
	  }
	  else
	  {
		  toDay += 31;
	  }
	 toMonth = toMonth - 1;
  }

	if (toMonth < fromMonth)
	{
		toMonth += 12;
		toYear -= 1;
	}
 
  int resultMonth = toMonth - fromMonth;
  int resultDay = toDay - fromDay;
  int resultYear = toYear - fromYear;

 printf("\n\n %d year(s) %02d month(s) and %02d day(s)\n", resultYear, resultMonth, resultDay);


 resultMonth *= 30;
 resultYear *= 365;
 
  int totalDays = resultMonth + resultYear + resultDay;
 printf("\nDays Passed: %d day(s)", totalDays);
 printf( "\n\n");

 return 0;
}

int getMonth(char token[]) 
{
	int n;
	if (token[0] < '0' || token[0]> '9' || token[1] < '0' || token[1]> '9')
		return 0;
	n = 10 * (token[0] - '0') + token[1] - '0';
	if (n > 12)
		return 0;
	return n;
}

int getDay(char token[]) 
{
	int n;
	if (token[0] < '0' || token[0]> '9' || token[1] < '0' || token[1]> '9')
		return 0;
	n = 10 * (token[0] - '0') + token[1] - '0';
	if (n > 31)
		return 0;
	return n;
}

int getYear(char token[]) {
	int n;
	if (token[0] < '0' || token[0]> '9' ||
		token[1] < '0' || token[1]> '9' ||
		token[2] < '0' || token[2]> '9' ||
		token[3] < '0' || token[3]> '9')
		return 0;
	n = 1000 * (token[0] - '0') + 100 * (token[1] - '0') + 10 * (token[2] - '0') + token[3] - '0';
	return n;
}

void handleCount(void) 
{
  int  mon1, day1, year1, mon2, day2, year2;
  
	char date1[25];
	char date2[25];
	char last_char = getCommandWord(date1, 25);
  
	if (last_char != ' ')
  {
		fprintf(stderr, "\nError: too few parameters");
  }
	last_char = getCommandWord(date2, 25);
	if (last_char != '\n')
  {
		fprintf(stderr, "\nError: too many parameters");
  }
	if (date1[2] != '/' || date1[5] != '/' || date2[2] != '/' || date2[5] != '/')
  {
		fprintf(stderr, "\nError: invalid dates");
  }
  
	date1[2] = date1[5] = date2[2] = date2[5] = '\0';
	mon1 = getMonth(date1);
  day1 = getDay(date1 + 3);
  year1 = getYear(date1 + 6);
  
	mon2 = getMonth(date2);
	day2 = getDay(date2 + 3);
	year2 = getYear(date2 + 6);
  
	if (isValidDate(mon1, day1, year1) == 0 && isValidDate(mon2, day2, year2) == 0)
  {
		fprintf(stderr, "\nError: invalid date(s) passed\n");
  }
	else if ((mon1 * day1 * year1 * mon2 * day2 * year2) == 0)
	{
		fprintf(stderr, "\nError: invalid date(s) passed\n");
	}
  else
  {
	  printf("\nDate 1: %d/%d/%d\nDate 2: %d/%d/%d", mon1, day1, year1, mon2, day2, year2);
	  printf("  ", count(mon1, day1, year1, mon2, day2, year2));
  }

}

int monthDays(int month, int year) {
	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		if (isLeapYear(year))
			return 29;
		else
			return 28;
	}
	return -1;
}

int isValidDate(int day, int month, int year) 
{ //was month, day , year
//	return year >= 1 && month >= 1 && month <=12 && day >= 1 && day <= monthDays(month, year);
    int is_valid = 1, is_leap = 0;

    if (year >= 1800 && year <= 9999) 
    {

        //  check whether year is a leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
        {
            is_leap = 1;
        }

        // check whether mon is between 1 and 12
        if(month >= 1 && month <= 12)
        {
            // check for days in feb
            if (month == 2)
            {
                if (is_leap && day == 29) 
                {
                    is_valid = 1;
                }
                else if(day > 28) 
                {
                    is_valid = 0;
                }
            }

            // check for days in April, June, September and November
            else if (month == 4 || month == 6 || month == 9 || month == 11) 
            {
                if (day > 30)
                {
                    is_valid = 0;
                }
            }

            // check for days in rest of the months
            // i.e Jan, Mar, May, July, Aug, Oct, Dec
            else if(day > 31)
            {
                is_valid = 0;
            }
        }
        else
        {
            is_valid = 0;
        }
    }
    else
    {
        is_valid = 0;
    }

    return is_valid;

}

int compareTo(int fromMonth, int fromDay, int fromYear, int toMonth, int toDay, int toYear)
{
	//returns negative int if from date < to date
	//return zero if from date == to date
	//returns positive int otherwise
	if (fromYear != toYear)
		return fromYear - toYear;
	if (fromMonth != toMonth)
		return fromMonth - toMonth;
	return fromDay - toDay;
}
int isLeapYear(int year) //97 leap years in every 400 years... 365 days + 97/400
{
	return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);//2000, 2020, 1600, 2024, 2016,... are leap years...
	//1900, 1800, 1700, 2100, 2002, 2019,... are not leap years...
}
