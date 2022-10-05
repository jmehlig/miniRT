#include "minirt.h"

t_scene	built_graphic(t_scene scene, t_graphic graphic)
{
	// init scene & camera
	init_graphic(&graphic);
	put_scene(scene, &graphic);
	set_graphic(&graphic, &scene);
	scene.graphic = graphic;
	return (scene);
}

void	init_graphic(t_graphic *graphic)
{
	graphic->zoom = 1;
	graphic->z_shift = 1;
	graphic->x_shift = 960;
	graphic->y_shift = 540;
	graphic = new_graphic(graphic);
}

t_graphic	*new_graphic(t_graphic *g)
{
	if (g->mlx != NULL)
		mlx_destroy_window(g->mlx, g->win);
	if (g->img != NULL)
		mlx_destroy_image(g->mlx, g->img);
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "miniRT");
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->addr = mlx_get_data_addr(g->img, &(g->bpp), &(g->line_l), &(g->end));
	return (g);
}

void	set_graphic(t_graphic *graphic, t_scene *scene)
{
	mlx_put_image_to_window(graphic->mlx, graphic->win, graphic->img, 0, 0);
	mlx_hook(graphic->win, 2, 1L << 0, ft_exit, graphic);
	mlx_hook(graphic->win, 17, 1L << 17, ex, graphic);
	scene->graphic = *graphic;
	mlx_key_hook(graphic->win, keys, scene);
	mlx_loop(graphic->mlx);
}

/*
    scene->vp.width = ;
	scene->vp.height = scene->vp.width * HEIGHT / WIDTH;
	scene->vp.x_pix = scene->vp.width / WIDTH;
	scene->vp.y_pix = scene->vp.height / HEIGHT;
*/