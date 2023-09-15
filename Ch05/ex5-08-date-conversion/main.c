/* Exercise 5-8. There is no error checking in day_of_year 
 * or month_day. Remedy this defect. */
#include <stdio.h>

/* Constants */
#define SEP         "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"      
#define YEAR        2
#define N_MONTHS    13      /* number of months +1 */ 

/* Macros */
#define IS_LEAP_YEAR(year) ((year%4 == 0 && year%100 != 0) || year%400 == 0)

/* Global variables */
static char daytab[YEAR][N_MONTHS] = {  
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, 
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
char *monthtab[N_MONTHS] = { "None", "January", "February", 
    "March", "April", "May", "June", "July", "August", 
    "September", "October", "November", "December" };

/* Function prototypes */
int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

void print_date(int month, int day, int yearday, int year);

/* Date Conversion Driver */
int main(void)
{
    int year, month, day, yearday;
    
    printf(SEP "\tDate Conversion\n" SEP);
    printf("Enter year:\t");
    scanf("%d", &year);
    printf("Enter month:\t");
    scanf("%d", &month);
    printf("Enter day:\t");
    scanf("%d", &day);

    yearday = day_of_year(year, month, day);
    month_day(year, yearday, &month, &day);

    /* Print results */
    print_date(month, day, yearday, year);
}


/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{  
	int i, leap;
	
	leap = IS_LEAP_YEAR(year); 
	for (i = 1; i < month; i++)
		day += daytab[leap][i]; 
	return day;
}

/* month_day: set month, day from day of year */  
void month_day(int year, int yearday, int *pmonth, int *pday)
{  
	int i, leap;
	
	leap = IS_LEAP_YEAR(year); 
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i]; 
	*pmonth = i;
	*pday = yearday;
}

/* print_date: print month and day */
void print_date(int month, int day, int yearday, int year)
{
    if ((yearday % 10) == 1)
    {
        if (day == 1)
            printf(SEP "%s %dst is the %dst day of %d\n", monthtab[month], day, yearday, year);
        else if (day == 2)
            printf(SEP "%s %dnd is the %dst day of %d\n", monthtab[month], day, yearday, year);
        else if (day == 3)
            printf(SEP "%s %drd is the %dst day of %d\n", monthtab[month], day, yearday, year);
        else
            printf(SEP "%s %dth is the %dst day of %d\n", monthtab[month], day, yearday, year);

    }
    else if ((yearday % 10) == 2)
    {
        if (day == 2)
            printf(SEP "%s %dnd is the %dnd day of %d\n", monthtab[month], day, yearday, year);
        else if (day == 3)
            printf(SEP "%s %drd is the %dnd day of %d\n", monthtab[month], day, yearday, year);
        else
            printf(SEP "%s %dth is the %dnd day of %d\n", monthtab[month], day, yearday, year);
    }   
    else if ((yearday % 10) == 3)
    {
        if (day == 3)
            printf(SEP "%s %drd is the %drd day of %d\n", monthtab[month], day, yearday, year);
        else
            printf(SEP "%s %dth is the %drd day of %d\n", monthtab[month], day, yearday, year);
    }
    else
    {
        if (day == 1)
            printf(SEP "%s %dst is the %dth day of %d\n", monthtab[month], day, yearday, year);
        else if (day == 2)
            printf(SEP "%s %dnd is the %dth day of %d\n", monthtab[month], day, yearday, year);
        else if (day == 3)
            printf(SEP "%s %drd is the %dth day of %d\n", monthtab[month], day, yearday, year);
        else
            printf(SEP "%s %dth is the %dth day of %d\n", monthtab[month], day, yearday, year);
    }
}
