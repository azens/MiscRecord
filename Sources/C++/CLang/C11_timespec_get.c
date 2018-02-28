// #include <stdio.h>
// #include <time.h>
// int main(void)
// {
// struct timespec ts;
// timespec_get(&ts, TIME_UTC);
// char buff[100];
// strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
// printf("Current time: %s.%09ld UTC\n", buff, ts.tv_nsec);
// }

#include <time.h>
#include <memory.h>
#include <stdio.h>
int main()
{
    struct timespec time;
    memset(&time, 0, sizeof(time));
    clock_gettime(CLOCK_REALTIME, &time);
    printf("%d----->%d\n", time.tv_sec, time.tv_nsec);
    return 0;
}