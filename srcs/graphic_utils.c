/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:21:54 by jmehlig           #+#    #+#             */
/*   Updated: 2022/09/12 17:00:13 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//Needs to access the free function??
//That does not free stuff, how did that work for FdF??
int	ft_exit(int keycode, t_graphic *graphic)
{
	if (keycode == 53)
		exit(0);
	return (graphic->zoom - graphic->zoom);
}

//Needs to be the free function??
//That does not free stuff, how did that work for FdF??
// Why is that even int?? It does not return anything
int	ex(void)
{
	exit(0);
}

int	keycode_check(int keycode)
{
	if (keycode == 69 || keycode == 78 || keycode == 125 || keycode == 126
		|| keycode == 0 || keycode == 2 || keycode == 13 || keycode == 1)
		return (1);
	return (0);
}

int	keys(int keycode, t_scene *scene)
{
	t_graphic		graphic;

	graphic = scene->graphic;
	if (keycode == 69)
		graphic.zoom++;
	if (keycode == 78 && graphic.zoom > 1)
		graphic.zoom--;
	if (keycode == 125)
		graphic.z_shift++;
	if (keycode == 126)
		graphic.z_shift--;
	if (keycode == 0)
		graphic.x_shift -= 10;
	if (keycode == 2)
		graphic.x_shift += 10;
	if (keycode == 1)
		graphic.y_shift += 10;
	if (keycode == 13)
		graphic.y_shift -= 10;
	if (keycode_check(keycode))
		built_graphic(*scene, graphic);
	return (0);
}
