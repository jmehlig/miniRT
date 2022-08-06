/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:50:04 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/06 23:27:19 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene *in_scene(t_scene *scene, char *line)
{
    if (ft_strncmp(line, "A ", 2) == 0)
        scene = parse_ambi_light(scene, ft_split(line, ' '));
    else if (ft_strncmp(line, "C ", 2) == 0)
        scene = parse_camera(scene, ft_split(line, ' '));
    else if (ft_strncmp(line, "L ", 2) == 0)
        scene = parse_light(scene, ft_split(line, ' '));
    else if (ft_strncmp(line, "sp ", 3) == 0)
        scene = parse_sphere(scene, ft_split(line, ' '));
    else if (ft_strncmp(line, "pl ", 3) == 0)
        scene = parse_plane(scene, ft_split(line, ' '));
    else if (ft_strncmp(line, "cy ", 3) == 0)
        scene = parse_cylinder(scene, ft_split(line, ' '));
    else
        simple_error();
    return (scene);
}

t_scene *readfile(t_scene *scene, int fd)
{
    char *line;

    while (1)
    {
        line = get_next_line(fd);
        printf("heeere\n");
        if (!line)
            break ;
        scene = in_scene(scene, line);
        ft_free(line);
    }
    return (scene);
}

void parser(t_scene *scene, char *argv)
{
    int fd;
    char *src;

    src = ft_strjoin("./tests/", argv);
    fd = open(src, O_RDONLY);
    if (fd < 0)
        simple_error();
    scene = readfile(scene, fd);
    //printf("%f   %i,%i,%i\n", scene->ambi_light.ratio, scene->ambi_light.colors[0], scene->ambi_light.colors[1], scene->ambi_light.colors[2]);
    //printf("%f,%f,%f    %f,%f,%f   %i\n", scene->camera.view[0], scene->camera.view[1], scene->camera.view[2], scene->camera.orientation[0], scene->camera.orientation[1], scene->camera.orientation[2], scene->camera.fov);
    //printf("%f,%f,%f    %f    %i,%i,%i\n", scene->light.coordinates[0], scene->light.coordinates[1], scene->light.coordinates[2], scene->light.brightness, scene->light.colors[0], scene->light.colors[1], scene->light.colors[2]);
    // t_sphere *sphere =  scene->sphere->content;
    // printf("%f,%f,%f   %f     %i,%i,%i\n", sphere->center[0], sphere->center[1], sphere->center[2], sphere->diameter, sphere->colors[0], sphere->colors[1], sphere->colors[2]);
    // t_plane *plane = scene->plane->content;
    // printf("%f,%f,%f    %f,%f,%f   %i,%i,%i\n", plane->coordinates[0], plane->coordinates[1], plane->coordinates[2], plane->orientation[0], plane->orientation[1], plane->orientation[2], plane->colors[0], plane->colors[1], plane->colors[2]);
    t_cylinder *cy= scene->cylinder->content;
    printf("%f,%f,%f    %f,%f,%f   %f     %f     %i,%i,%i\n", cy->coordinates[0], cy->coordinates[1], cy->coordinates[2], cy->orientation[0], cy->orientation[1], cy->orientation[2], cy->diameter, cy->height, cy->colors[0], cy->colors[1], cy->colors[2]);
    exit(1);
}