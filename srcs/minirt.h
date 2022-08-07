/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:01:55 by jmehlig           #+#    #+#             */
/*   Updated: 2022/08/07 13:53:34 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "../minilibx_macos/mlx.h"
# include "../includes/libft/libft.h"
# include "../includes/get_next_line/get_next_line.h"

typedef struct s_ambi_light
{
    float ratio;
    int *colors; //malloc - free_scene
}   t_ambi_light;

typedef struct s_camera
{
    float *view; //malloc - free_scene
    float *orientation; //malloc - free_scene
    int fov;
}   t_camera;

typedef struct s_light
{
    float *coordinates; //malloc - free_scene
    float brightness;
    int *colors; //malloc - free_scene
}   t_light;

typedef struct s_sphere
{
    float *center; //malloc - free_sphere
    float diameter;
    int *colors; //malloc - free_sphere
}   t_sphere;

typedef struct s_plane
{
    float *coordinates; //malloc
    float *orientation; //malloc
    int *colors;
}   t_plane;

typedef struct s_cylinder
{
    float *coordinates;
    float *orientation;
    float diameter;
    float height;
    int *colors;
}   t_cylinder;

//sphere, plane, cylinder can be declared more often
//linked list?
typedef struct s_scene
{
    t_ambi_light ambi_light;
    t_camera camera;
    t_light light;
    t_list *sphere; //malloc
    t_list *plane; //malloc
    t_list *cylinder; //malloc
}   t_scene;

//exit.c
void simple_error_free(t_scene *scene);
void text_error_free(char *str, t_scene *scene);
void simple_error();
void text_error(char *str);

//parser.c
t_scene *in_scene(t_scene *scene, char *tmp);
t_scene *readfile(t_scene *scene, int fd);
void parser(t_scene *scene, char *argv);

//parser_setting.c
t_scene *parse_ambi_light(t_scene *scene, char **line_split);
t_scene *parse_camera(t_scene *scene, char **line_split);
t_scene *parse_light(t_scene *scene, char **line_split);

//parser_figures.c
void	free_content(void *content);
t_scene *parse_sphere(t_scene *scene, char **line_split);
t_scene *parse_plane(t_scene *scene, char **line_split);
t_scene *parse_cylinder(t_scene *scene, char **line_split);

//ft_stof.c
bool ft_string_digit(char *str);
float ft_stof(char *str);

//parser_utils.c
bool ft_bit_range(int array[3]);
bool ft_unit_range(float array[3]);
int *parse_color(char **line_split, int i);
float *split_coordinates(char *str);

//image.c
void put_scene(t_scene scene);

//free.c
void free_sphere(t_list **sphere_list);
void free_plane(t_list **plane_list);
void free_cylinder(t_list **cylinder_list);
void free_scene(t_scene **scene);

#endif