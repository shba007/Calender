#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <conio.h>
#include <time.h>
#include <io.h>

#define _O_U8TEXT 0x00040000
#define _O_U16TEXT 0x00020000

int getkey();
int LeapYear(int, int *);

int main()
{
	//Gregorian Calendar
	int d, m, y;
	int i, num, tab = 0, key = 71;
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int daysUpToMonth[][12] = {
		{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334},
		{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335}};
	char monthsName[][10] = {"January", "February", "March", "April",
							 "May", "June", "July", "August", "September",
							 "October", "November", "December"};
	char weekdays[][4] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

	time_t t = time(NULL);
	struct tm *ct = localtime(&t);

	while (1)
	{
		system("cls");
		switch (key)
		{
		case 71:
			d = 1;
			m = ct->tm_mon + 1;
			y = ct->tm_year + 1900;
			(LeapYear(1900, &daysInMonth[1]) == 1) ? (d += 366 - (daysUpToMonth[1][0] + 1)) : (d += 365 - (daysUpToMonth[0][0] + 1));
			for (i = 1900, num = 0; i < y; i++)
			{
				if ((i % 400 == 0) || (i % 100 != 0 && i % 4 == 0))
					num++;
			}
			d += (y - 1901) * 365 + num;
			(LeapYear(y, &daysInMonth[1]) == 1) ? (d += daysUpToMonth[1][m - 1]) : (d += daysUpToMonth[0][m - 1]);
			tab = d % 7;
			break;
		case 72:
			(LeapYear(y, &daysInMonth[1]) == 0) ? (tab += 1) : (tab += 2);
			tab %= 7;
			y++;
			break;
		case 75:
			if (m > 1)
				m--;
			else
			{
				y--;
				m = 12;
			}
			if ((daysInMonth[m - 1] - tab) % 7)
				tab = (tab - daysInMonth[m - 1]) + 7 * ((daysInMonth[m - 1] - tab) / 7 + 1);
			else
				tab = 0;
			break;
		case 77:
			if (m < 12)
			{
				m++;
				tab = (tab + daysInMonth[m - 2]) % 7;
			}
			else
			{
				y++;
				m = 1;
				tab = (tab + daysInMonth[m - 1]) % 7;
			}
			break;
		case 79:
			exit(0);
		case 80:
			(LeapYear(y - 1, &daysInMonth[1]) == 0) ? (tab -= 1) : (tab -= 2);
			(tab < 0) ? (tab += 7) : (tab);
			y--;
			break;
		}

		printf("\t\t\t\t\t\t%s %d\n", monthsName[m - 1], y);
		putchar('\n');
		for (i = 0; i < 7; i++)
			printf("\t%s\t", weekdays[i]);
		printf("\n\n\n");
		for (i = 0; i < tab; i++)
			printf("\t\t");
		for (d = 1; d <= daysInMonth[m - 1]; d++, i++)
		{
			if (i % 7 == 0 && i)
				printf("\n\n\n");
			printf("\t%d\t", d);
		}
		putchar('\n');
		_setmode(_fileno(stdout), _O_U16TEXT);
		wprintf(L"\n\t\t\t\x25B2 to increase the year");
		wprintf(L"\t\t\t\x25BC to decrease the year");
		wprintf(L"\n\t\t\t\x25BA to increase the month");
		wprintf(L"\t\t\t\x25C4 to decrease the month");
		wprintf(L"\n\t\t\tHome to current month and End Key to exit");
		_setmode(_fileno(stdout), _O_TEXT);
		LeapYear(y, &daysInMonth[1]);
		key = getkey();
	}
	return 0;
}

int getkey()
{
	int as, sc;
	as = getch();
	sc = 0;
	if (as == 0)
		sc = getch();
	return sc;
}

int LeapYear(int year, int *d)
{
	if ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0))
	{
		*d = 29;
		return 1;
	}
	else
	{
		*d = 28;
		return 0;
	}
}