/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_figures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:51:10 by jmehlig           #+#    #+#             */
/*   Updated: 2022/09/20 17:23:46 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_content(void *content)
{
	free(content);
}

t_scene *parse_sphere(t_scene *scene, char **line_split, int fd)
{
    t_sphere *sphere;
    t_list *new;
	t_vector *temp;

    sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        simple_error_free(scene, line_split, fd);
	if (line_split[4] && ft_strncmp(line_split[4], "\n", 1) == 0);
    else if (!line_split[3] || line_split[4])
        text_error_free("Not the right sp input", scene, line_split, fd);
    temp = split_coordinates(line_split[1]);
	sphere->center = subtract_vec(temp, scene->camera.origin);
	//printf("\n%f %f %f\n", sphere->center->x, sphere->center->y, sphere->center->z);
	free (temp);
    if (!sphere->center)
        text_error_free("'sp': Not the right center input", scene, line_split, fd);
    sphere->diameter = ft_stof(line_split[2]);
    sphere->colors = parse_color(line_split, 3);
    if (!sphere->colors)
        text_error_free("'sp': Not the right colors input", scene, line_split, fd);
    if (!ft_bit_range(sphere->colors))
        text_error_free("'sp': colors out of range", scene, line_split, fd);   
    new = ft_lstnew(sphere);
    if (!new)
        simple_error_free(scene, line_split, fd);
    ft_lstadd_back(&scene->sphere, new);
    return(scene);
}

t_scene *parse_plane(t_scene *scene, char **line_split, int fd)
{
    t_plane *plane;
    t_list *new;
    
    plane = malloc(sizeof(t_plane));
    if (!plane)
        simple_error_free(scene, line_split, fd);
	if (line_split[4] && ft_strncmp(line_split[4], "\n", 1) == 0);
    else if (!line_split[3] || line_split[4])
        text_error_free("Not the right pl input", scene, line_split, fd);
    plane->coordinates = split_coordinates(line_split[1]);
    if (!plane->coordinates)
        text_error_free("'pl': Not the right coordinates input", scene, line_split, fd);
    plane->orientation = split_coordinates(line_split[2]);
    if (!ft_unit_range(plane->orientation))
        text_error_free("'pl': orientaion out of range", scene, line_split, fd);
    plane->colors = parse_color(line_split, 3);
    if (!plane->colors)
        text_error_free("'pl': Not the right colors input", scene, line_split, fd);
    if (!ft_bit_range(plane->colors))
        text_error_free("'pl': colors out of range", scene, line_split, fd);
    new = ft_lstnew(plane);
    if(!new)
        simple_error_free(scene, line_split, fd);
    ft_lstadd_back(&scene->plane, new);
    return(scene);
}

t_scene *parse_cylinder(t_scene *scene, char **line_split, int fd)
{
    t_cylinder *cylinder;
    t_list *new;

    cylinder = malloc(sizeof(t_cylinder));
    if (!cylinder)
        simple_error_free(scene, line_split, fd);
	if (line_split[6] && ft_strncmp(line_split[6], "\n", 1) == 0);
    else if (!line_split[5] || line_split[6])
        text_error_free("Not the right cy input", scene, line_split, fd);
    cylinder->coordinates = split_coordinates(line_split[1]);
    if (!cylinder->coordinates)
        text_error_free("'cy': Not the right coordinates input", scene, line_split, fd);
    cylinder->orientation = split_coordinates(line_split[2]);
    if (!ft_unit_range(cylinder->orientation))
        text_error_free("'cy': orientaion out of range", scene, line_split, fd);
    cylinder->diameter = ft_stof(line_split[3]);
    cylinder->height = ft_stof(line_split[4]);
    cylinder->colors = parse_color(line_split, 5);
    if (!cylinder->colors)
        text_error_free("'cy': Not the right colors input", scene, line_split, fd);
    if (!ft_bit_range(cylinder->colors))
        text_error_free("'cy': colors out of range", scene, line_split, fd);
    new = ft_lstnew(cylinder);
    if(!new)
        simple_error_free(scene, line_split, fd);
    ft_lstadd_back(&scene->cylinder, new);
    return(scene);
}