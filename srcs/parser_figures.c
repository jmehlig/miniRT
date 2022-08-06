/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_figures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:51:10 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/06 22:41:13 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_content(void *content)
{
	free(content);
}

t_scene *parse_sphere(t_scene *scene, char **line_split)
{
    t_sphere *sphere;
    t_list *new;

    sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        simple_error();
    if (!line_split[3] || line_split[4])
        text_error("Not the right sp input");
    sphere->center = split_coordinates(line_split[1]);
    if (!sphere->center)
        text_error("'sp': Not the right center input");
    sphere->diameter = ft_stof(line_split[2]);
    sphere->colors = parse_color(line_split, 3);
    if (!sphere->colors)
        text_error("'sp': Not the right colors input");
    if (!ft_bit_range(sphere->colors))
        text_error("'sp': colors out of range");   
    new = ft_lstnew(sphere);
    if (!new) //better put simple_error and free there (plus protection!!)
    {
        free(sphere);
        //free_scene(); 
        ft_lstclear(&scene->sphere, free_content);
    }
    ft_lstadd_back(&scene->sphere, new);
    ft_split_del(&line_split);
    return(scene);
}

t_scene *parse_plane(t_scene *scene, char **line_split)
{
    t_plane *plane;
    t_list *new;
    
    plane = malloc(sizeof(t_plane));
    if (!plane)
        simple_error();
    if (!line_split[3] || line_split[4])
        text_error("Not the right pl input");
    plane->coordinates = split_coordinates(line_split[1]);
    if (!plane->coordinates)
        text_error("'pl': Not the right coordinates input");
    plane->orientation = split_coordinates(line_split[2]);
    if (!ft_unit_range(plane->orientation))
        text_error("'pl': orientaion out of range");
    plane->colors = parse_color(line_split, 3);
    if (!plane->colors)
        text_error("'pl': Not the right colors input");
    if (!ft_bit_range(plane->colors))
        text_error("'pl': colors out of range");
    new = ft_lstnew(plane);
    if(!new)
        simple_error();
    ft_lstadd_back(&scene->plane, new);
    ft_split_del(&line_split);
    return(scene);
}

t_scene *parse_cylinder(t_scene *scene, char **line_split)
{
    t_cylinder *cylinder;
    t_list *new;

    cylinder = malloc(sizeof(t_cylinder));
    if (!cylinder)
        simple_error();
    if (!line_split[5] || line_split[6])
        text_error("Not the right cy input");
    cylinder->coordinates = split_coordinates(line_split[1]);
    if (!cylinder->coordinates)
        text_error("'cy': Not the right coordinates input");
    cylinder->orientation = split_coordinates(line_split[2]);
    if (!ft_unit_range(cylinder->orientation))
        text_error("'cy': orientaion out of range");
    cylinder->diameter = ft_stof(line_split[3]);
    cylinder->height = ft_stof(line_split[4]);
    cylinder->colors = parse_color(line_split, 5);
    if (!cylinder->colors)
        text_error("'cy': Not the right colors input");
    if (!ft_bit_range(cylinder->colors))
        text_error("'cy': colors out of range");
    ft_split_del(&line_split);
    new = ft_lstnew(cylinder);
    if(!new)
        simple_error();
    ft_lstadd_back(&scene->cylinder, new);
    return(scene);
}