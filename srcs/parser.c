
#include "minirt.h"

t_scene *in_scene(t_scene *scene, char **split_line, int fd)
{
//    int i = 0;
//    printf("\n");
//    while (split_line[i] != NULL)
//    {
// 		printf("%s|", split_line[i]);
// 		i++;
//    }
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
    char *tmp;
    char **split_line;
    int i;

    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        //split_line = ft_split_multi(line, " \t"); ----> is a mess
        split_line = ft_split(line, ' ');
		i = 0;
        while (split_line[i] != NULL)
        {
			tmp = ft_strtrim(split_line[i], "\t ");
            split_line[i] = tmp;
            i++;
		}
        ft_free(line);
        scene = in_scene(scene, split_line, fd);
    }
    scene->vp.width = 2 * tanf((scene->camera.fov / 2) * (M_PI / 180));
	scene->vp.height = scene->vp.width * HEIGHT / WIDTH;
	scene->vp.x_pix = scene->vp.width / WIDTH;
	scene->vp.y_pix = scene->vp.height / HEIGHT;
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
	if (scene->camera.direction == NULL || scene->ambi_light.colors == NULL || scene->light.coordinates == NULL)
		simple_error();
    close(fd);
}