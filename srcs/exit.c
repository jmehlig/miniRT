/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:33:30 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/07 13:54:05 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//free in the errors!!!!

void simple_error_free(t_scene *scene)
{
    free(&scene);
    simple_error();
}

void text_error_free(char *str, t_scene *scene)
{
    free(&scene);
    text_error(str);
}

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