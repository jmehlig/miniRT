#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "../minilibx_macos/mlx.h"
# include "../includes/libft/libft.h"
# include "../includes/get_next_line/get_next_line.h"

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_vector
{
	float   x;
	float   y;
	float   z;
}   t_vector;

typedef struct s_color
{
	int r;
	int g;
	int b;
}	t_color;

typedef struct s_graphic
{
	int			zoom;
	int			z_shift;
	int			x_shift;
	int			y_shift;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_l;
	int			end;
}				t_graphic;

typedef struct s_pixel
{
	float distance;
	int *colors;
}   t_pixel;

typedef struct s_dist
{
	float		dist;
	float		min_dist;
	t_vector	*n;
	t_vector	*p;
	int			*closest_col;
	float		light;
}	t_dist;

typedef struct s_ambi_light
{
	float ratio;
	int *colors; //malloc - free_scene
}   t_ambi_light;

typedef struct s_camera
{
	t_vector    *origin; //malloc - free_scene- coordinates??
	t_vector    *direction; //malloc - free_scene
	int fov;
}   t_camera;

typedef struct s_light
{
	t_vector *coordinates; //malloc - free_scene
	float brightness;
	int *colors; //malloc - free_scene
}   t_light;

typedef struct s_sphere
{
	t_vector *center; //malloc - free_sphere
	float diameter; // radius???
	int *colors; //malloc - free_sphere
}   t_sphere;

typedef struct s_plane
{
	t_vector *coordinates; //malloc
	t_vector *orientation; //malloc
	int *colors;
}   t_plane;

typedef struct s_cylinder
{
	t_vector *coordinates;
	t_vector *orientation;
	float diameter;
	float height;
	int *colors;
}   t_cylinder;

typedef struct s_view_plane 
{
	float   width;
	float   height;
	float   x_pix;
	float   y_pix;
}   t_view_plane;

typedef struct s_draw
{
	int		mlx_x;
	int		mlx_y;
	int		x_angle;
	int		y_angle;
	int		color;
	float	x_ray;
	float	y_ray;
	t_vector	*ray;
}	t_draw;

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
	t_graphic graphic; // pointer???
	t_view_plane vp;
}   t_scene;

//exit.c
void simple_error_free(t_scene *scene, char **split_line, int fd);
void text_error_free(char *str, t_scene *scene, char **split_line, int fd);
void simple_error();
void text_error(char *str);
void error_exit(int code);

//parser.c
t_scene *in_scene(t_scene *scene, char **split_line, int fd);
t_scene *readfile(t_scene *scene, int fd);
void parser(t_scene *scene, char *argv);

//parser_setting.c
t_scene *parse_ambi_light(t_scene *scene, char **line_split, int fd);
t_scene *parse_camera(t_scene *scene, char **line_split, int fd);
t_scene *parse_light(t_scene *scene, char **line_split, int fd);

//parser_figures.c
void	free_content(void *content);
t_scene *parse_sphere(t_scene *scene, char **line_split, int fd);
t_scene *parse_plane(t_scene *scene, char **line_split, int fd);
t_scene *parse_cylinder(t_scene *scene, char **line_split, int fd);

//ft_stof.c
bool ft_string_digit(char *str);
float ft_stof(char *str);

//parser_utils.c
void set_scene_null(t_scene *scene, t_graphic *graphic);
bool ft_bit_range(int array[3]);
bool ft_unit_range(t_vector *vector);
int *parse_color(char **line_split, int i);
t_vector *split_coordinates(char *str);

//image.c
void put_scene(t_scene scene, t_graphic *graphic);

//free.c
void free_sphere(t_list **sphere_list);
void free_plane(t_list **plane_list);
void free_cylinder(t_list **cylinder_list);
void free_scene(t_scene **scene);

//graphic.c
void    init_graphic(t_graphic *graphic);
void    set_graphic(t_graphic *graphic, t_scene *scene);
t_graphic	*new_graphic(t_graphic *graphic);
t_scene	built_graphic(t_scene scene, t_graphic graphic);

//graphic_utils.c
int	ft_exit(int keycode, t_graphic *graphic);
int	ex(void);
int	keys(int keycode, t_scene *scene);

//math.c
t_vector    *subtract_vec(t_vector *v1, t_vector *v2);
float        len_vec(t_vector *v);
float        dot_prod_vec(t_vector *v1, t_vector *v2);
void         norm_vec(t_vector *v);
t_vector    *new_vector(float x, float y, float z);
t_vector    *add_vec(t_vector *v1, t_vector *v2);
// t_vector    *scalar_multiply_vec(float x, t_vector *v2);
t_vector	*scalar_multi(t_vector *vec, float a);

//image.c 
void			put_pix_to_image(t_graphic *graphic, int color, int x, int y);
// t_view_plane    *get_view_plane(float width, float height, float fov);
int				create_rgb(int r, int g, int b);
// void			loop_x_y(float x_angle, float y_angle, t_view_plane *vp, t_scene scene, t_graphic *graphic);
// void			put_scene(t_scene scene, t_graphic *graphic);
int				get_color(t_scene scene, t_vector *ray);
float 			compute_lighting(t_dist *d, t_scene scene, t_vector *ray, t_dist *shadow);
int				*scalar_multi_colors(int *colors, float a);
void			init_dist(t_dist *dist);

//intersection.c
float 		sphere_intersect(t_camera *cam, t_vector *ray, t_sphere *sphere);
t_vector	*ortho_project_in_plane(t_vector *in, t_vector *normal_vec, t_vector *point);
t_dist		*cylinder_intersect(t_camera *cam, t_vector *ray, t_cylinder *cylinder);
float		plane_intersect(t_plane *pl, t_camera *cam, t_vector *ray);

//intersection_cylinder.c
float	basis_change_back(t_vector *point, t_vector *n, t_vector *ray, t_cylinder *cy);
float	cylinder_caps(char loc, t_vector *ray, t_camera *cam, t_cylinder *cylinder);
t_camera *camera_project(t_camera *cam, t_cylinder *cylinder);
t_vector *ray_project(t_vector *ray, t_cylinder *cylinder, t_camera	*camera_cpy);
float	cylinder_circle(t_cylinder *cylinder, t_camera	*camera_cpy, t_vector *ray_cpy);

//float			sphere_intersect(t_camera *cam, t_vector *ray, t_sphere *sphere);

//color
// t_color	color_from_rgb(int r, int g, int b);
// t_color			color_from_hex(int hex);
// int	hex_from_color(t_color color);

#endif