/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:14:57 by kmorunov          #+#    #+#             */
/*   Updated: 2022/10/30 17:16:42 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	parse_ambi_light(t_scene scene, char **line_split, int fd)
{
	if (ft_comp_float(scene.a_light.ratio, -1.0) != 0)
		msg_error("A was declared more than once", line_split, fd);
	if (ft_len_double(line_split) != 3)
		msg_error("Not the right 'A' input", line_split, fd);
	scene.a_light.ratio = ft_stof(line_split[1], fd);
	if (ft_f_less_f(scene.a_light.ratio, 0.0)
		|| ft_f_greater_f(scene.a_light.ratio, 1.0))
		msg_error("'A': light_ratio out of range", line_split, fd);
	scene.a_light.color = parse_color(line_split, 2, fd);
	if (!ft_bit_range(scene.a_light.color))
		msg_error("'A': colors out of range", line_split, fd);
	return (scene);
}

t_scene	parse_camera(t_scene scene, char **line_split, int fd)
{
	if (scene.camera.fov != -1)
		msg_error("C was declared more than once", line_split, fd);
	if (ft_len_double(line_split) != 4)
		msg_error("Not the right 'C' input", line_split, fd);
	scene.camera.origin = split_coord(line_split, 1, fd);
	scene.camera.direction = split_coord(line_split, 2, fd);
	if (!ft_unit_range(scene.camera.direction))
		msg_error("'C': orientaion out of range", line_split, fd);
	scene.camera.fov = ft_atoi(line_split[3]);
	if (!ft_string_digit(line_split[3])
		|| scene.camera.fov < 0 || scene.camera.fov > 180)
		msg_error("'C': fov out of range", line_split, fd);
	return (scene);
}

t_scene	parse_light(t_scene scene, char **line_split, int fd)
{
	if (ft_comp_float(-1, scene.light.bright) != 0)
		msg_error("L was declared more than once", line_split, fd);
	if (ft_len_double(line_split) != 4)
		msg_error("Not the right L input", line_split, fd);
	scene.light.coord = split_coord(line_split, 1, fd);
	scene.light.bright = ft_stof(line_split[2], fd);
	if (ft_f_less_f(scene.light.bright, 0.0)
		|| ft_f_greater_f(scene.light.bright, 1.0))
		msg_error("'L': brightness out of range", line_split, fd);
	scene.light.color = parse_color(line_split, 3, fd);
	if (!ft_bit_range(scene.light.color))
		msg_error("'L': colors out of range", line_split, fd);
	return (scene);
}
