# Date Differ C

Calculates the **difference** between **two dates** with old format.

## Using

```sh
$ gcc date-diff.c -o date-diff
./date-diff
```

## Example
```
const char* date_start = "1970-01-01 00:00:01";
const char* date_end = "2038-01-19 03:14:07";

char* diff_ago = date_diff(date_start, date_end);
printf("%s\n", diff_ago); // 68 years ago

diff_ago = date_diff(date_end, date_start);
printf("%s\n", diff_ago); // 68 years ago
```

© Copyright 2022, Max Base
