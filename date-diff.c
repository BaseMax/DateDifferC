/*
 * Date: 2022/06/10
 * Author: Max Base
 * Name: Date Differ (C)
 * Repository: github.com/basemax/DateDifferC
 * Description: Calculates the difference between two dates with old format.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *strptime(const char * __restrict, const char * __restrict, struct tm * __restrict);

// Date format is timestamp "YYYY-MM-DD hh:mm:ss"
// We want to return the difference in days between two dates in `ago` format.
// Example:
//   date-diff "2020-01-01 00:00:00" "2020-01-02 00:00:00"
//   => "1 day ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-03 00:00:00"
//   => "2 days ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-04 00:00:00"
//   => "3 days ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-05 00:00:00"
//   => "4 days ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-06 00:00:00"
//   => "5 days ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-07 00:00:00"
//   => "6 days ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-08 00:00:00"
//   => "7 days ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-09 00:00:00"
//   => "1 week ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-10 00:00:00"
//   => "2 weeks ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-11 00:00:00"
//   => "3 weeks ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-12 00:00:00"
//   => "4 weeks ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-13 00:00:00"
//   => "5 weeks ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-14 00:00:00"
//   => "6 weeks ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-15 00:00:00"
//   => "7 weeks ago"
//   date-diff "2020-01-01 00:00:00" "2020-01-16 00:00:00"
//   => "1 month ago"
//   date-diff "2019-01-01 00:00:00" "2022-02-01 00:00:00"
//   => "2 years ago"
char* date_diff(const char* date_start, const char* date_end) {
    struct tm tm_start, tm_end;
    char* result = NULL;
    int days_diff = 0;
    int weeks_diff = 0;
    int months_diff = 0;
    int years_diff = 0;
    int hours_diff = 0;
    int minutes_diff = 0;

    // Parse the dates
    if (strptime(date_start, "%Y-%m-%d %H:%M:%S", &tm_start) == NULL) {
        return NULL;
    }
    if (strptime(date_end, "%Y-%m-%d %H:%M:%S", &tm_end) == NULL) {
        return NULL;
    }

    // Swap date_start and date_end if date_end is less than date_start
    if (tm_start.tm_year > tm_end.tm_year) {
        struct tm tmp = tm_start;
        tm_start = tm_end;
        tm_end = tmp;
    } else if (tm_start.tm_year == tm_end.tm_year) {
        if (tm_start.tm_mon > tm_end.tm_mon) {
            struct tm tmp = tm_start;
            tm_start = tm_end;
            tm_end = tmp;
        } else if (tm_start.tm_mon == tm_end.tm_mon) {
            if (tm_start.tm_mday > tm_end.tm_mday) {
                struct tm tmp = tm_start;
                tm_start = tm_end;
                tm_end = tmp;
            }
        }
    }

    // Calculate the difference in minutes
    minutes_diff = (tm_end.tm_hour - tm_start.tm_hour) * 60 + (tm_end.tm_min - tm_start.tm_min);

    // Calculate the difference in hours
    hours_diff = (tm_end.tm_hour - tm_start.tm_hour) + (tm_end.tm_min - tm_start.tm_min) / 60;

    // Calculate the difference in days
    days_diff = (tm_end.tm_year - tm_start.tm_year) * 365 + (tm_end.tm_mon - tm_start.tm_mon) * 30 + (tm_end.tm_mday - tm_start.tm_mday);
    if (days_diff < 0) {
        days_diff = 0;
    }

    // Calculate the difference in weeks
    weeks_diff = days_diff / 7;
    if (weeks_diff < 0) {
        weeks_diff = 0;
    }

    // Calculate the difference in months
    months_diff = (tm_end.tm_year - tm_start.tm_year) * 12 + (tm_end.tm_mon - tm_start.tm_mon);
    if (months_diff < 0) {
        months_diff = 0;
    }

    // Calculate the difference in years
    years_diff = tm_end.tm_year - tm_start.tm_year;
    if (years_diff < 0) {
        years_diff = 0;
    }

    // Build the result string
    if (days_diff == 0) {
        if (hours_diff == 0) {
            if (minutes_diff == 0) {
                result = (char*) malloc(sizeof(char) * (strlen("now") + 1));
                strcpy(result, "now");
            } else {
                result = (char*) malloc(sizeof(char) * (strlen("1 minute ago") + 1));
                strcpy(result, "1 minute ago");
            }
        } else if (hours_diff == 1) {
            result = strdup("1 hour ago");
        } else {
            result = malloc(sizeof(char) * (strlen("2 hours ago") + 1));
            sprintf(result, "%d hours ago", hours_diff);
        }
    } else if (days_diff == 1) {
        result = (char*) malloc(sizeof(char) * (strlen("yesterday") + 1));
        strcpy(result, "yesterday");
    } else if (days_diff < 7) {
        result = (char*) malloc(sizeof(char) * (strlen("%d days ago") + 1));
        sprintf(result, "%d days ago", days_diff);
    } else if (weeks_diff < 4) {
        result = (char*) malloc(sizeof(char) * (strlen("%d weeks ago") + 1));
        sprintf(result, "%d weeks ago", weeks_diff);
    } else if (months_diff < 12) {
        result = (char*) malloc(sizeof(char) * (strlen("%d months ago") + 1));
        sprintf(result, "%d months ago", months_diff);
    } else {
        result = (char*) malloc(sizeof(char) * (strlen("%d years ago") + 1));
        sprintf(result, "%d years ago", years_diff);
    }

    return result;

    // if (diff < 0) {
    //     strcpy(ago, "invalid date");
    // } else if (diff < 7) {
    //     sprintf(ago, "recent now");
    // } else if (diff < 60) {
    //     sprintf(ago, "%d seconds ago", diff);
    // } else if (diff < 3600) {
    //     sprintf(ago, "%d minutes ago", diff / 60);
    // } else if (diff < 86400) {
    //     sprintf(ago, "%d hours ago", diff / 3600);
    // } else if (diff < 604800) {
    //     sprintf(ago, "%d days ago", diff / 86400);
    // } else if (diff < 2629743) {
    //     sprintf(ago, "%d weeks ago", diff / 604800);
    // } else if (diff < 31556926) {
    //     sprintf(ago, "%d months ago", diff / 2629743);
    // } else {
    //     sprintf(ago, "%d years ago", diff / 31556926);
    // }
    // return ago;
}

int main() {
    const char* date_start = "1970-01-01 00:00:01";
    const char* date_end = "2038-01-19 03:14:07";
    
    char* diff_ago = date_diff(date_start, date_end);
    printf("%s\n", diff_ago);

    diff_ago = date_diff(date_end, date_start);
    printf("%s\n", diff_ago);

    return 0;
}
