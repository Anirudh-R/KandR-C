#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int* month, int* day);

// Program to sort input lines
int main(void)
{
    int m, d, dy;

    dy = day_of_year(1988, 2, 3);

    printf("%d\n", dy);

    month_day(1987, 34, &m, &d);

    printf("%d %d\n", m, d);

    return 0;
}


int day_of_year(int year, int month, int day)
{
	int leap, i;

	leap = year%4==0 && year%100!=0 || year%400==0;

	if(!(month>=1 && month<=12))
    {
        printf("Error: Invalid month.\n");
        return 0;
    }

    if(!(day>=1 && day<=*(*(daytab+leap)+month)))
    {
        printf("Error: Invalid day.\n");
        return 0;
    }

	for(i=1; i<month; i++)
		day += *(*(daytab+leap)+i);

	return day;
}

void month_day(int year, int yearday, int* month, int* day)
{
	int leap, i;

	leap = year%4==0 && year%100!=0 || year%400==0;

	if(!(yearday>=1 && yearday<=365+leap))
    {
        printf("Error: Invalid day of year.\n");
        *month = 0;
        *day = 0;
        return;
    }

	for(*day=0, i=1; *day + *(*(daytab+leap)+i) < yearday; i++)
			*day += *(*(daytab+leap)+i);

	*day = yearday - *day;
	*month = i;
}
