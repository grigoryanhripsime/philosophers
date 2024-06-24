#include "philosophers.h"

//int gettimeofday(struct timeval *restrict tp, void *restrict tzp);

size_t get_time(void)
{
    struct timeval tv;
    static size_t smt;

    if (smt == 0)
    {
        if (gettimeofday(&tv, NULL))
            return (0);
        smt = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    }
    if (gettimeofday(&tv, NULL))
        return (0);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - smt);
}

int ft_usleep(int mls)
{
    int start;
    int end;

    start = get_time();
    usleep(mls * 1000);
    end = get_time();
    return (end - start);
}