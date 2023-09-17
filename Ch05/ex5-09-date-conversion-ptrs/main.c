/* Exercise 5-9. There is no error checking in day_of_year 
 * or month_day. Remedy this defect. */
#include <stdio.h>
#include <stdlib.h>

/* Constants */
#define SEP         "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"      
#define N_MONTHS    13      /* number of months +1 */ 

/* Macros */
#define IS_LEAP_YEAR(year) ((year%4 == 0 && year%100 != 0) || year%400 == 0)

/* Global variables */
static char daytab[][N_MONTHS] = {  
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, 
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static char *monthtab[] = { "Invalid month", "January", "February", 
    "March", "April", "May", "June", "July", "August", 
    "September", "October", "November", "December", NULL 
};

/* Function prototypes */
int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

char *month_name(int n);
void print_date(int month, int day, int yearday, int year);

/* Date Conversion Driver */
int main(int argc, char *argv[])
{
    int year, month, day, yearday;
    
    /* Handle Invalid usage */
    if (argc != 4)
    {
        printf(SEP "Usage: %s <year> <month> <day>\n" SEP, argv[0]);
        return 1;
    }
    /* Parse & validate user input */
    year = atoi(argv[1]);
    month = atoi(argv[2]);
    day = atoi(argv[3]);
    if (year < 1 || year > 9999)
    {
        printf(SEP "Year must be between 1 and 9999\n" SEP);
        return 1;
    }
    if (month < 1 || month > 12)
    {
        printf(SEP "Month must be between 1 and 12\n" SEP);
        return 1;
    }
    if (day > daytab[IS_LEAP_YEAR(year)][month])    /* Check if day exists in month */ 
    {
        printf(SEP "For %s, day must be between 1 and %d!\n" SEP, 
               month_name(month), daytab[IS_LEAP_YEAR(year)][month]);
        return 1;
    }

    /* Print Header */
    printf(SEP "\tDate Conversion\n" SEP);

    /* Calculate day of year */
    yearday = day_of_year(year, month, day);
    month_day(year, yearday, &month, &day);

    /* Print results */
    print_date(month, day, yearday, year);
    
    return 0;
}


/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{  
	int i;                      /* to iterate */
    int leap;                   /* to check if leap year */        
    char *p_days;               /* to point to daytab */
	
	leap = IS_LEAP_YEAR(year);  /* Check if leap year */
    p_days = &daytab[leap][1];  /* Pointer to number of days in month */

	for (i = 1; i < month; i++)
		day += *p_days++;       /* Add number of days in month */ 

	return day;                 /* Return number of days in year */
}

/* month_day: set month, day from day of year */  
void month_day(int year, int yearday, int *pmonth, int *pday)
{  
	int i, leap;
    char *p_days;            
	
	leap = IS_LEAP_YEAR(year); 
    p_days = &daytab[leap][1];   /* Pointer to number of days in month */

	for (i = 1; yearday > *p_days; i++)
		yearday -= *p_days++; 
	*pmonth = i;
	*pday = yearday;
}

/* month_name: print month name */
char *month_name(int n)
{
    return (n < 1 || n > 12) ? monthtab[0] : monthtab[n];
}

void print_date(int month, int day, int yearday, int year)
{
    char *day_suffix, *yeardaySuffix;

    /* Set 'day' suffix */
    if (day > 3 && day < 21)
        day_suffix = "th";
    else
        switch (day % 10)
        {
            case 1:  day_suffix = "st"; break;
            case 2:  day_suffix = "nd"; break;
            case 3:  day_suffix = "rd"; break;
            default: day_suffix = "th"; break;
        }

    /* Set 'yearday' suffix */
    if (yearday > 3 && yearday < 21)
        yeardaySuffix = "th";
    else
        switch (yearday % 10)
        {
            case 1:  yeardaySuffix = "st"; break;
            case 2:  yeardaySuffix = "nd"; break;
            case 3:  yeardaySuffix = "rd"; break;
            default: yeardaySuffix = "th"; break;
        }

    /* Print results */
    printf("\t %s %d%s, %d\n", month_name(month), day, day_suffix, year);
    printf(SEP "%s %d%s is the %d%s day of %d\n", 
           month_name(month), day, day_suffix, yearday, yeardaySuffix, year);
}
