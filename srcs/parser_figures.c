/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_figures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:14:50 by kmorunov          #+#    #+#             */
/*   Updated: 2022/10/30 17:17:30 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_content(void *content)
{
	free(content);
}

t_obj	parse_sphere(t_obj object, char **line_split, int fd)
{
	t_sphere	*sphere;
	t_list		*new;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
	{
		ft_split_del(&line_split);
		p_error(fd);
	}
	if (ft_len_double(line_split) != 4)
		msg_error("Not the right sp input", line_split, fd);
	sphere->center = split_coord(line_split, 1, fd);
	sphere->diam = ft_stof(line_split[2], fd);
	sphere->color = parse_color(line_split, 3, fd);
	if (!ft_bit_range(sphere->color))
		msg_error("'sp': colors out of range", line_split, fd);
	new = ft_lstnew(sphere);
	if (!new)
		msg_error("Error\n", line_split, fd);
	ft_lstadd_back(&object.sphere, new);
	return (object);
}

t_obj	parse_plane(t_obj obj, char **line_split, int fd)
{
	t_plane	*plane;
	t_list	*new;

	plane = malloc(sizeof(t_plane));
	if (!plane)
	{
		ft_split_del(&line_split);
		p_error(fd);
	}
	if (ft_len_double(line_split) != 4)
		msg_error("Not the right pl input", line_split, fd);
	plane->coord = split_coord(line_split, 1, fd);
	plane->orien = split_coord(line_split, 2, fd);
	if (!ft_unit_range(plane->orien))
		msg_error("'pl': orientaion out of range", line_split, fd);
	plane->color = parse_color(line_split, 3, fd);
	if (!ft_bit_range(plane->color))
		msg_error("'pl': colors out of range", line_split, fd);
	new = ft_lstnew(plane);
	if (!new)
		msg_error("Error\n", line_split, fd);
	ft_lstadd_back(&obj.plane, new);
	return (obj);
}

static t_cylinder	*new_cy(char **line_split, int fd)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
	{
		ft_split_del(&line_split);
		p_error(fd);
	}
	return (cylinder);
}

t_obj	parse_cylinder(t_obj obj, char **line_split, int fd)
{
	t_cylinder	*cylinder;
	t_list		*new;

	cylinder = new_cy(line_split, fd);
	if (ft_len_double(line_split) != 6)
		msg_error("Not the right cy input", line_split, fd);
	cylinder->coord = split_coord(line_split, 1, fd);
	cylinder->orien = split_coord(line_split, 2, fd);
	if (!ft_unit_range(cylinder->orien))
		msg_error("'cy': orientaion out of range", line_split, fd);
	cylinder->diameter = ft_stof(line_split[3], fd);
	cylinder->height = ft_stof(line_split[4], fd);
	cylinder->color = parse_color(line_split, 5, fd);
	if (!ft_bit_range(cylinder->color))
		msg_error("'cy': colors out of range", line_split, fd);
	new = ft_lstnew(cylinder);
	if (!new)
		msg_error("Error\n", line_split, fd);
	ft_lstadd_back(&obj.cylinder, new);
	return (obj);
}
