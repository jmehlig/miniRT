/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:51:01 by jmehlig           #+#    #+#             */
/*   Updated: 2022/09/16 04:42:03 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void set_scene_null(t_scene *scene, t_graphic *graphic)
{
    scene->ambi_light.colors= NULL;
    scene->camera.origin =  NULL;
    scene->camera.direction = NULL;
    scene->light.coordinates = NULL;
    scene->light.colors = NULL;
    scene->sphere = NULL;
    scene->plane = NULL;
    scene->cylinder = NULL;
    graphic->mlx = NULL;
    graphic->img = NULL;
    scene->vp.height = 0;
    scene->vp.width = 0;
    scene->vp.x_pix = 0;
    scene->vp.y_pix = 0;  
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

//this should also look for normalized??
bool ft_unit_range(t_vector *vec)
{
    if (ft_f_less_f(vec->x, -1.0) || ft_f_greater_f(vec->x, 1.0))
        return (false);
    else if (ft_f_less_f(vec->y, -1.0) || ft_f_greater_f(vec->y, 1.0))
        return (false);
    else if (ft_f_less_f(vec->z, -1.0) || ft_f_greater_f(vec->z, 1.0))
        return (false);
    else if (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z != 1)
        norm_vec(vec);
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
    {
        ft_free(colors);
        ft_split_del(&split_colors);
        return (NULL);
    }
    colors[0] = ft_atoi(split_colors[0]);
    colors[1] = ft_atoi(split_colors[1]);
    colors[2] = ft_atoi(split_colors[2]);
    ft_split_del(&split_colors);
    return (colors);
}

t_vector *split_coordinates(char *str)
{
    char **split_coord;
    t_vector *coordinates;
    
    coordinates = malloc(sizeof(t_vector *));
    if (!coordinates)
        return (NULL);
    split_coord = ft_split(str, ',');
    if (!split_coord[0] || !split_coord[1] || !split_coord[2] || split_coord[3])
        return (NULL);
    coordinates->x = ft_stof(split_coord[0]);
    coordinates->y = ft_stof(split_coord[1]);
    coordinates->z = ft_stof(split_coord[2]);
    ft_split_del(&split_coord);
    return (coordinates);
}