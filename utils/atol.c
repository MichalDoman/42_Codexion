#include "../codexion.h"


long    ft_atol(char *str)
{
    int     i;
    char    sign;
    long    result;

    i = 0;
    while (str[i] == ' ' || str[i] >= 9 && str[i] <= 13)
        i++;
    sign = 1;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    result = 0;
    while (str[i] >= '0' && str[i] <= '9')
        result = result * 10 + (str[i] - '0');
    return (result * sign);
}
