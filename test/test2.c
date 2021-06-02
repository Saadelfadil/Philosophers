#include <stdio.h>
#include <sys/time.h>

long long get_time_stamp()
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int main()
{
    long long str;

    str = get_time_stamp();
    printf("%lld\n", str);
    // printf("%d\n", (int)get_time_stamp());
    return (0);
}