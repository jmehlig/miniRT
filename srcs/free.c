/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 21:11:00 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/06 21:35:54 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//not protected!!!!
void free_scene(t_scene *scene)
{
    ft_free(scene->ambi_light.colors);
    ft_free(scene->camera.view);
    ft_free(scene->camera.orientation);
    ft_free(scene->light.coordinates);
    ft_free(scene->light.colors);
}