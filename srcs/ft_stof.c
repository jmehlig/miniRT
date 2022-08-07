/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:54:49 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/07 17:18:47 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//convert string to float

static long ft_power(int base, int exponent)
{
    long power;

    power  = 1;
    while (exponent > 0)
    {
        power = power * base;
        exponent--;
    }
    return (power);
}

bool ft_string_digit(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (!ft_isdigit(str[i]) && str[i] != '\n')
        {
            printf("'%c'\n", str[i]);
            return (false);
        }
        i++;
    }
    return (true);
}

static float ft_convert(int deci_places, char *tmp, char *tmp2)
{
    float result;
    long  power;
    int   int1;
    int   int2;

    if (!ft_string_digit(tmp2))
        text_error("Float input is wrong");
    int1 = ft_atoi(tmp);
    int2 = ft_atoi(tmp2);
    //printf("%d ", int1);
    //printf("%i\n", int2);
    power = int1 * ft_power(10, deci_places);
    power = power + int2;
    result = (float)power / (float)(ft_power(10, deci_places));
    if (ft_strncmp(tmp, "-0", 2) == 0)
        result = -result;
    ft_free(tmp);
    ft_free(tmp2);
    return (result);
}

float ft_stof(char *str)
{
    int  deci_separator;
    int  i;
    char *tmp;
    char *tmp2;

    i = 0;
    deci_separator = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '.')
        {
            deci_separator = i;
            break ;
        }
        i++;
    }
    if (str[i] == '\0')
    {
        tmp2 = ft_strdup("0");
        deci_separator = i;
    }
    else
        tmp2 = ft_substr(str, deci_separator + 1, ft_strlen(str) - deci_separator);
    tmp = ft_substr(str, 0, deci_separator);
    return(ft_convert(ft_strlen(tmp2), tmp, tmp2));
}