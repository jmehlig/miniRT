/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:33:30 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/06 22:16:01 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//free in the errors!!!!

void simple_error(void)
{
    write(2, "\e[;31mError\n", 12);
    exit(1);
}

void text_error(char *str)
{
    write(2, "\e[;31mError\n", 12);
    write(2, str, ft_strlen(str));
    exit(1);
}