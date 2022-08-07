/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 21:11:00 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/07 15:42:55 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void free_sphere(t_list **sphere_list)
{
    t_list	*temp;
    t_sphere *sphere;

	while ((*sphere_list))
	{
		temp = *sphere_list;
        sphere = (*sphere_list)->content;
        if (sphere->center)
            ft_free(sphere->center);
        if (sphere->colors)
            ft_free(sphere->colors);
		*sphere_list = (*sphere_list)->next;
		ft_lstdelnode(sphere_list, temp->content);
	}
}

void free_plane(t_list **plane_list)
{
    t_list	*temp;
    t_plane *plane;

	while ((*plane_list))
	{
		temp = *plane_list;
        plane = (*plane_list)->content;
        if (plane->coordinates)
            ft_free(plane->coordinates);
        if (plane->orientation)
            ft_free(plane->orientation);
        if (plane->colors)
            ft_free(plane->colors);
		*plane_list = (*plane_list)->next;
		ft_lstdelnode(plane_list, temp->content);
	}
}

void free_cylinder(t_list **cylinder_list)
{
    t_list	*temp;
    t_cylinder *cylinder;

	while ((*cylinder_list))
	{
		temp = *cylinder_list;
        cylinder = (*cylinder_list)->content;
        if (cylinder->coordinates)
            ft_free(cylinder->coordinates);
        if (cylinder->orientation)
            ft_free(cylinder->orientation);
        if (cylinder->colors)
            ft_free(cylinder->colors);
		*cylinder_list = (*cylinder_list)->next;
		ft_lstdelnode(cylinder_list, temp->content);
	}
}

void free_scene(t_scene **scene)
{
    if ((*scene)->ambi_light.colors)
        ft_free((*scene)->ambi_light.colors);
    if ((*scene)->camera.view)
        ft_free((*scene)->camera.view);
    if ((*scene)->camera.orientation)
        ft_free((*scene)->camera.orientation);
    if ((*scene)->light.coordinates)
        ft_free((*scene)->light.coordinates);
    if ((*scene)->light.colors)
        ft_free((*scene)->light.colors);
    if ((*scene)->sphere)
        free_sphere(&(*scene)->sphere);
    if ((*scene)->plane)
        free_plane(&(*scene)->plane);
    if ((*scene)->cylinder)
        free_cylinder(&(*scene)->cylinder);
}