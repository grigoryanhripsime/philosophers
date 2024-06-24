#include "philosophers.h"

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int ft_strlen(char *s)
{
    int i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
        i++;
    return (i);
}

int	check_num(char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
        i++;
    while (str[i] && str[i] == '0')
        i++;
    if (ft_strlen(str + i) > 10)
        return (0);
    while (str[i] >= '0' && str[i] <= '9')
    {
        num = (num * 10) + (str[i] - '0');
        i++;
    }
	if (str[i] || num > 2147483647)
		return (0);
	return (num);
}
