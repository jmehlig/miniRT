/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:15:08 by kmorunov          #+#    #+#             */
/*   Updated: 2022/10/30 17:04:22 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_minirt	*in_scene(t_minirt *mt, char **split_line, int fd)
{
	if (ft_strncmp(split_line[0], "A", 2) == 0)
		mt->scene = parse_ambi_light(mt->scene, split_line, fd);
	else if (ft_strncmp(split_line[0], "C", 2) == 0)
		mt->scene = parse_camera(mt->scene, split_line, fd);
	else if (ft_strncmp(split_line[0], "L", 2) == 0)
		mt->scene = parse_light(mt->scene, split_line, fd);
	else if (ft_strncmp(split_line[0], "sp", 3) == 0)
		mt->obj = parse_sphere(mt->obj, split_line, fd);
	else if (ft_strncmp(split_line[0], "pl", 3) == 0)
		mt->obj = parse_plane(mt->obj, split_line, fd);
	else if (ft_strncmp(split_line[0], "cy", 3) == 0)
		mt->obj = parse_cylinder(mt->obj, split_line, fd);
	else if (ft_strncmp(split_line[0], "\n", 1) == 0 || split_line[0][0] == '#')
		split_line[0][0] = '\n';
	else
		msg_error(split_line[0], split_line, fd);
	ft_split_del(&split_line);
	return (mt);
}

char	*ft_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\t' || line[i] == '\v' || line[i] == '\f')
			line[i] = ' ';
		i++;
	}
	return (line);
}

static t_minirt	*readfile(t_minirt *mt, int fd)
{
	char	*line;
	char	*tmp;
	char	**split_line;
	int		i;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = ft_whitespace(line);
		split_line = ft_split(line, ' ');
		i = 0;
		while (split_line[i] != NULL)
		{
			tmp = ft_strtrim(split_line[i], "\t ");
			split_line[i] = tmp;
			i++;
		}
		ft_free(line);
		mt = in_scene(mt, split_line, fd);
	}
	return (mt);
}

void	parser(t_minirt *mt, char *argv)
{
	int		fd;
	char	*src;
	int		len;

	len = ft_strlen(argv);
	if (argv[len - 3] != '.' || argv[len - 2] != 'r' || argv[len - 1] != 't')
		msg_error("The file has to be a .rt file!", NULL, -1);
	src = ft_strjoin("./scenes/", argv);
	fd = open(src, O_RDONLY);
	ft_free(src);
	if (fd < 0)
		msg_error("Couldn't open input file!", NULL, fd);
	mt = readfile(mt, fd);
	if (mt->scene.camera.fov == -1
		|| ft_comp_float(mt->scene.a_light.ratio, -1.0) == 0
		|| ft_comp_float(mt->scene.light.bright, -1.0) == 0)
		p_error(fd);
	close(fd);
}
