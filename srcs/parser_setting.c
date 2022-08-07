/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_setting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:11:21 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/07 14:14:59 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene *parse_ambi_light(t_scene *scene, char **line_split)
{
    if (scene->ambi_light.ratio)
        text_error_free("A was declared more than once", scene);
    if (!line_split[1] || !line_split[2] || line_split[3])
        text_error_free("Not the right 'A' input", scene);
    scene->ambi_light.ratio = ft_stof(line_split[1]);
    if (ft_f_less_f(scene->ambi_light.ratio, 0.0) || ft_f_greater_f(scene->ambi_light.ratio, 1.0))
        text_error_free("'A': light_ratio out of range", scene);
    scene->ambi_light.colors = parse_color(line_split, 2);
    if (!scene->ambi_light.colors)
        text_error_free("'A': Not the right colors input", scene);
    if (!ft_bit_range(scene->ambi_light.colors))
        text_error_free("'A': colors out of range", scene);
    ft_split_del(&line_split);
    return (scene);
}

t_scene *parse_camera(t_scene *scene, char **line_split)
{
    if (scene->camera.view)
        text_error_free("C was declared more than once", scene);
    if (!line_split[3] || line_split[4])
        text_error_free("Not the right 'C' input", scene);
    scene->camera.view = split_coordinates(line_split[1]);
    if (!scene->camera.view)
        text_error_free("'C': Not the right view input", scene);
    scene->camera.orientation = split_coordinates(line_split[2]);
    if (!ft_unit_range(scene->camera.orientation))
        text_error_free("'C': orientaion out of range", scene);
    scene->camera.fov = ft_atoi(line_split[3]);
    if (!ft_string_digit(line_split[3]) || scene->camera.fov < 0 || scene->camera.fov > 180)
        text_error_free("'C': fov out of range", scene);
    ft_split_del(&line_split);
    return (scene);
}

t_scene *parse_light(t_scene *scene, char **line_split)
{
    if (scene->light.brightness)
        text_error_free("L was declared twice", scene);
    if (!line_split[3] || line_split[4])
        text_error_free("Not the right L input", scene);
    scene->light.coordinates = split_coordinates(line_split[1]);
    scene->light.brightness =  ft_stof(line_split[2]);
    if (ft_f_less_f(scene->light.brightness, 0.0) || ft_f_greater_f(scene->light.brightness, 1.0))
        text_error_free("'L': brightness out of range", scene);
    scene->light.colors = parse_color(line_split, 3);
    if (!scene->light.colors)
        text_error_free("'L': Not the right colors input", scene);
    if (!ft_bit_range(scene->light.colors))
        text_error_free("'L': colors out of range", scene);
    ft_split_del(&line_split);
    return (scene);
}