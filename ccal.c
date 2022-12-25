#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>

const time_t day = 60*60*24;	/* One day in seconds */
const char *wday[] = { "NI", "po", "wt", "śr", "cz", "pt", "SO" };

/* Print all days of year (current or given as first arg). */
int
main(int argc, char **argv)
{
	int year;
	time_t timestamp;
	struct tm *tm;

	if ((timestamp = time(NULL)) < 0) {
		errx(1, "ERR time");
	}
	if (!(tm = localtime(&timestamp))) {
		errx(1, "ERR initial localtime");
	}
	if (argc > 1) {
		/* I don't care about arbument validation. */
		tm->tm_year = atoi(argv[1]) - 1900;
	}
	tm->tm_sec   = 0;
	tm->tm_min   = 0;
	tm->tm_hour  = 0;
	tm->tm_mday  = 1;	/* Tell me why! */
	tm->tm_mon   = 0;
	tm->tm_isdst = 0;
	tm->tm_wday  = 0;
	tm->tm_yday  = 0;
	if ((timestamp = mktime(tm)) < 0) {
		errx(1, "ERR mktime");
	}
	year = tm->tm_year;
	while (tm->tm_year == year) {
		printf("%.4d.%.2d.%.2d %s\n",
		       tm->tm_year + 1900,
		       tm->tm_mon + 1,
		       tm->tm_mday,
		       wday[tm->tm_wday]);
		timestamp += day;
		if (!(tm = localtime(&timestamp))) {
			errx(1, "ERR localtime");
		}
	}
	return 0;
}
