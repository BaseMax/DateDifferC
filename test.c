/*
 * Date: 2022/06/10
 * Author: Max Base
 * Name: Date Differ (C)
 * Repository: github.com/basemax/DateDifferC
 * Description: Calculates the difference between two dates with old format.
 */

#include <stdio.h>
#include <stdlib.h>

char* date_diff(const char* date_start, const char* date_end);

int main() {
    const char* date_start = "1970-01-01 00:00:01";
    const char* date_end = "2038-01-19 03:14:07";
    
    char* diff_ago = date_diff(date_start, date_end);
    printf("%s\n", diff_ago);

    diff_ago = date_diff(date_end, date_start);
    printf("%s\n", diff_ago);

    return 0;
}
