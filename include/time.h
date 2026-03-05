/* Stub time.h for cc compiler */
#ifndef _TIME_H
#define _TIME_H
typedef long time_t;
typedef long clock_t;
struct tm {
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
};
time_t time(time_t *t);
struct tm *localtime(time_t *timep);
struct tm *gmtime(time_t *timep);
time_t mktime(struct tm *tm);
char *ctime(time_t *timep);
char *asctime(struct tm *tm);
long strftime(char *s, long max, char *format, struct tm *tm);
clock_t clock(void);
#define CLOCKS_PER_SEC 1000000
#endif
