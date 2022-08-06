/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:01:05 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/06 22:27:09 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//parser : Einlesen  des Files mit gnl, ueberpruefen ob richtiges Fomrat, richtige Range

// Aufbau des Fensters, wie in FdF? Geht das schneller?

//Annahme: Eingabe erfolgt mit ./minirt file.rt

int main(int argc, char *argv[])
{
    t_scene scene;

    if (argc != 2)
        text_error("Not the right input - must be of form ./minirt file.rt\n");
    parser(&scene, argv[1]);
    put_scene(scene);
    //free_scene(&scene);
    return (0);
}
