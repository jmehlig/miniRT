/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:01:05 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/07 14:03:03 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//parser : Einlesen  des Files mit gnl, ueberpruefen ob richtiges Fomrat, richtige Range

// Aufbau des Fensters, wie in FdF? Geht das schneller?

//Annahme: Eingabe erfolgt mit ./minirt file.rt

int main(int argc, char *argv[])
{
    t_scene scene;
    t_scene *scene_free;

    if (argc != 2)
        text_error("Not the right input - must be of form ./minirt file.rt\n");
    parser(&scene, argv[1]);
    put_scene(scene);
    scene_free = &scene;
    free_scene(&scene_free);
    system("leaks minirt");
    return (0);
}
