/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:51:01 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/07 15:39:45 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void set_scene_null(t_scene *scene)
{
    scene->ambi_light.colors= NULL;
    scene->camera.view = NULL;
    scene->camera.orientation = NULL;
    scene->light.coordinates = NULL;
    scene->light.colors = NULL;
    scene->sphere = NULL;
    scene->plane = NULL;
    scene->cylinder = NULL;
}

bool ft_bit_range(int array[3])
{
    if (array[0] < 0 || array[0] > 255)
        return (false);
    else if (array[1] < 0 || array[1] > 255)
        return (false);
    else if (array[2] < 0 || array[2] > 255)
        return (false);
    else
        return (true);
}

bool ft_unit_range(float array[3])
{
    if (ft_f_less_f(array[0], -1.0) || ft_f_greater_f(array[0], 1.0))
        return (false);
    else if (ft_f_less_f(array[1], -1.0) || ft_f_greater_f(array[1], 1.0))
        return (false);
    else if (ft_f_less_f(array[2], -1.0) || ft_f_greater_f(array[2], 1.0))
        return (false);
    else
        return (true);
}

int *parse_color(char **line_split, int i)
{
    int *colors;
    char **split_colors;

    colors = malloc(sizeof(int) * 3);
    if (!colors)
        simple_error();
    split_colors = ft_split(line_split[i], ',');
    if (!split_colors[0] || !split_colors[1] || !split_colors[2] || split_colors[3])
        return (NULL);
    colors[0] = ft_atoi(split_colors[0]);
    colors[1] = ft_atoi(split_colors[1]);
    colors[2] = ft_atoi(split_colors[2]);
    ft_split_del(&split_colors);
    return (colors);
}

float *split_coordinates(char *str)
{
    char **split_coord;
    float *coordinates;
    
    coordinates = malloc(sizeof(float) * 3);
    if (!coordinates)
        simple_error();
    split_coord = ft_split(str, ',');
    if (!split_coord[0] || !split_coord[1] || !split_coord[2] || split_coord[3])
        return (NULL);
    coordinates[0] = ft_stof(split_coord[0]);
    coordinates[1] = ft_stof(split_coord[1]);
    coordinates[2] = ft_stof(split_coord[2]);
    ft_split_del(&split_coord);
    return (&coordinates[0]);
}