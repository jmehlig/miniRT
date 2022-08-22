/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:50:04 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/07 18:01:44 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene *in_scene(t_scene *scene, char **split_line, int fd)
{
    if (ft_strncmp(split_line[0], "A", 2) == 0)
        scene = parse_ambi_light(scene, split_line, fd);
    else if (ft_strncmp(split_line[0], "C", 2) == 0)
        scene = parse_camera(scene, split_line, fd);
    else if (ft_strncmp(split_line[0], "L", 2) == 0)
        scene = parse_light(scene, split_line, fd);
    else if (ft_strncmp(split_line[0], "sp", 3) == 0)
        scene = parse_sphere(scene, split_line, fd);
    else if (ft_strncmp(split_line[0], "pl", 3) == 0)
        scene = parse_plane(scene, split_line, fd);
    else if (ft_strncmp(split_line[0], "cy", 3) == 0)
        scene = parse_cylinder(scene, split_line, fd);
    else if (ft_strncmp(split_line[0], "\n", 1) == 0)
        split_line[0][0] = '\n'; //do nothing
    else
        simple_error_free(scene, split_line, fd);
    ft_split_del(&split_line);
    return (scene);
}

t_scene *readfile(t_scene *scene, int fd)
{
    char *line;
    char **split_line;

    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        split_line = ft_split(line, ' ');
        ft_free(line);
        scene = in_scene(scene, split_line, fd);
    }
    return (scene);
}

void parser(t_scene *scene, char *argv)
{
    int fd;
    char *src;

    src = ft_strjoin("./tests/", argv);
    fd = open(src, O_RDONLY);
    ft_free(src);
    if (fd < 0)
        simple_error();
    scene = readfile(scene, fd);
    printf("%f   %i,%i,%i\n", scene->ambi_light.ratio, scene->ambi_light.colors[0], scene->ambi_light.colors[1], scene->ambi_light.colors[2]);
    printf("%f,%f,%f    %f,%f,%f   %i\n", scene->camera.view[0], scene->camera.view[1], scene->camera.view[2], scene->camera.orientation[0], scene->camera.orientation[1], scene->camera.orientation[2], scene->camera.fov);
    printf("%f,%f,%f    %f    %i,%i,%i\n", scene->light.coordinates[0], scene->light.coordinates[1], scene->light.coordinates[2], scene->light.brightness, scene->light.colors[0], scene->light.colors[1], scene->light.colors[2]);
    t_sphere *sphere =  scene->sphere->content;
    printf("%f,%f,%f   %f     %i,%i,%i\n", sphere->center[0], sphere->center[1], sphere->center[2], sphere->diameter, sphere->colors[0], sphere->colors[1], sphere->colors[2]);
    sphere = scene->sphere->next->content;
    printf("%f,%f,%f   %f     %i,%i,%i\n", sphere->center[0], sphere->center[1], sphere->center[2], sphere->diameter, sphere->colors[0], sphere->colors[1], sphere->colors[2]);
    t_plane *plane = scene->plane->content;
    printf("%f,%f,%f    %f,%f,%f   %i,%i,%i\n", plane->coordinates[0], plane->coordinates[1], plane->coordinates[2], plane->orientation[0], plane->orientation[1], plane->orientation[2], plane->colors[0], plane->colors[1], plane->colors[2]);
    t_cylinder *cy= scene->cylinder->content;
    printf("%f,%f,%f    %f,%f,%f   %f     %f     %i,%i,%i\n", cy->coordinates[0], cy->coordinates[1], cy->coordinates[2], cy->orientation[0], cy->orientation[1], cy->orientation[2], cy->diameter, cy->height, cy->colors[0], cy->colors[1], cy->colors[2]);
    close(fd);
}