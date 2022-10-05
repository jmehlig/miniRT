
#include "minirt.h"

t_scene *parse_ambi_light(t_scene *scene, char **line_split, int fd)
{
    if (scene->ambi_light.colors)
        text_error_free("A was declared more than once", scene, line_split, fd);
	if (line_split[3] && ft_strncmp(line_split[3], "\n", 1) == 0);
    else if (!line_split[1] || !line_split[2] || line_split[3])
        text_error_free("Not the right 'A' input", scene, line_split, fd);
    scene->ambi_light.ratio = ft_stof(line_split[1]);
    if (ft_f_less_f(scene->ambi_light.ratio, 0.0) || ft_f_greater_f(scene->ambi_light.ratio, 1.0))
        text_error_free("'A': light_ratio out of range", scene, line_split, fd);
    scene->ambi_light.colors = parse_color(line_split, 2);
    if (!scene->ambi_light.colors)
        text_error_free("'A': Not the right colors input", scene, line_split, fd);
    if (!ft_bit_range(scene->ambi_light.colors))
        text_error_free("'A': colors out of range", scene, line_split, fd);
    return (scene);
}

t_scene *parse_camera(t_scene *scene, char **line_split, int fd)
{
    if (scene->camera.origin)
        text_error_free("C was declared more than once", scene, line_split, fd);
	if (line_split[4] && ft_strncmp(line_split[4], "\n", 1) == 0);
    else if (!line_split[3] || line_split[4])
        text_error_free("Not the right 'C' input", scene, line_split, fd);
    scene->camera.origin = split_coordinates(line_split[1]);
    if (!scene->camera.origin)
        text_error_free("'C': Not the right view input", scene, line_split, fd);
    scene->camera.direction = split_coordinates(line_split[2]);
    //printf("%f, %f, %f\n", scene->camera.orientation[0], scene->camera.orientation[1], scene->camera.orientation[2]);
    if (!ft_unit_range(scene->camera.direction))
        text_error_free("'C': orientaion out of range", scene, line_split, fd);
    scene->camera.fov = ft_atoi(line_split[3]);
    if (!ft_string_digit(line_split[3]) || scene->camera.fov < 0 || scene->camera.fov > 180)
        text_error_free("'C': fov out of range", scene, line_split, fd);
    return (scene);
}

t_scene *parse_light(t_scene *scene, char **line_split, int fd)
{
    if (ft_compare_float(0, scene->light.brightness) == 0)
    {
        text_error_free("L was declared more than once", scene, line_split, fd);
    }
	if (line_split[4] && ft_strncmp(line_split[4], "\n", 1) == 0);
    else if (!line_split[3] || line_split[4])
        text_error_free("Not the right L input", scene, line_split, fd);
    scene->light.coordinates = split_coordinates(line_split[1]);
    scene->light.brightness =  ft_stof(line_split[2]);
    if (ft_f_less_f(scene->light.brightness, 0.0) || ft_f_greater_f(scene->light.brightness, 1.0))
        text_error_free("'L': brightness out of range", scene, line_split, fd);
    scene->light.colors = parse_color(line_split, 3);
    if (!scene->light.colors)
        text_error_free("'L': Not the right colors input", scene, line_split, fd);
    if (!ft_bit_range(scene->light.colors))
        text_error_free("'L': colors out of range", scene, line_split, fd);
    return (scene);
}