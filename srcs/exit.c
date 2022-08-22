/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:33:30 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/07 18:16:54 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//free in the errors!!!!

void simple_error_free(t_scene *scene, char **split_line, int fd)
{
    close(fd);
    if (split_line)
        ft_split_del(&split_line);
    free_scene(&scene);
    simple_error();
}

void text_error_free(char *str, t_scene *scene, char **split_line, int fd)
{
    close (fd);
    if (split_line)
        ft_split_del(&split_line);
    free_scene(&scene);
    text_error(str);
}

void simple_error(void)
{
    system("leaks minirt");
    write(2, "\e[;31mError\n\e[;29m", 20);
    exit(1);
}

void text_error(char *str)
{
    system("leaks minirt");
    write(2, "\e[;31mError\n", 12);
    write(2, str, ft_strlen(str));
    write(2, "\n", 1);
    exit(1);
}