/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:11:21 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/06 22:38:40 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene *parse_ambi_light(t_scene *scene, char **line_split)
{
    if (scene->ambi_light.ratio)
        text_error("A was declared more than once");
    if (!line_split[1] || !line_split[2] || line_split[3])
        text_error("Not the right 'A' input");
    scene->ambi_light.ratio = ft_stof(line_split[1]);
    if (ft_f_less_f(scene->ambi_light.ratio, 0.0) || ft_f_greater_f(scene->ambi_light.ratio, 1.0))
        text_error("'A': light_ratio out of range");
    scene->ambi_light.colors = parse_color(line_split, 2);
    if (!scene->ambi_light.colors)
        text_error("'A': Not the right colors input");
    if (!ft_bit_range(scene->ambi_light.colors))
        text_error("'A': colors out of range");
    return (scene);
}

t_scene *parse_camera(t_scene *scene, char **line_split)
{
    if (scene->camera.view)
        text_error("C was declared more than once");
    if (!line_split[3] || line_split[4])
        text_error("Not the right 'C' input");
    scene->camera.view = split_coordinates(line_split[1]);
    if (!scene->camera.view)
        text_error("'C': Not the right view input");
    scene->camera.orientation = split_coordinates(line_split[2]);
    if (!ft_unit_range(scene->camera.orientation))
        text_error("'C': orientaion out of range");
    scene->camera.fov = ft_atoi(line_split[3]);
    if (!ft_string_digit(line_split[3]) || scene->camera.fov < 0 || scene->camera.fov > 180)
        text_error("'C': fov out of range");
    ft_split_del(&line_split);
    return (scene);
}

t_scene *parse_light(t_scene *scene, char **line_split)
{
    if (scene->light.brightness)
        text_error("L was declared twice");
    if (!line_split[3] || line_split[4])
        text_error("Not the right L input");
    scene->light.coordinates = split_coordinates(line_split[1]);
    scene->light.brightness =  ft_stof(line_split[2]);
    if (ft_f_less_f(scene->light.brightness, 0.0) || ft_f_greater_f(scene->light.brightness, 1.0))
        text_error("'L': brightness out of range");
    scene->light.colors = parse_color(line_split, 3);
    if (!scene->light.colors)
        text_error("'L': Not the right colors input");
    if (!ft_bit_range(scene->light.colors))
        text_error("'L': colors out of range");
    ft_split_del(&line_split);
    return (scene);
}