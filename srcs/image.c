#include "minirt.h"

// Unsere z-Richtung scheint ein Problem zu sein!!!

//actually put the graphics in
// if camera is assumed at (0, 0, 0) all pixels that get put, must be translated by camera position
// Perspective projection
// Ok, wir werden hier durch die einzelnen linked lists gehen, vielleicht noch einen 
// Formatanfang um das genaue Field of View zu bestimmen (mit festgelegtem Abstand 1)

//Kugelgleichung mit Mittelpunkt im Ursrung berechnen, am Ende um Vektor sphere->center verschieben
// Da Kugel jetzt im Ursprung kann sie mit x^2 + y^2 + z^2 = (sphere->diameter / 2)^2 = r^2 beschrieben werden
// Beachte: Bei Zentralprojektion ist Mittelpunkt in echt, nicht Mittelpunkt der Projektion

// bit-shifting to get color: gives back an int (4 bit), in it are 4 1bit numbers (for transperency, RGB), each stored in a different bit
bool	same_point(t_vector *ray, t_dist *d, t_scene scene, t_dist *shadow)
{
	bool		is_same;
	t_vector	*point;
	t_vector	*temp;

	is_same = false;
	temp = scalar_multi(ray, d->min_dist); //ray ist normalized
	point = add_vec(temp, scene.camera.origin); // getting the actual point we want to set the pixel for
	ft_free (temp);
	temp = subtract_vec(point, scene.light.coordinates); // now compute te vector between this point and the light
	//printf("%f %f", shadow->min_dist, len_vec(temp));
	if (ft_compare_float(shadow->min_dist, len_vec(temp)) == 0) // if the length of that vector is the same as the shortest distance coming from the light, it is closest to the light
		is_same = true; // The point we want to set is not in the shadow
	ft_free (temp);
	ft_free (point);
	return (is_same);
}

//what is about colors of the light??
// get the color, while having it multiplied with a ratio from 0-1, depending on the ambient lightning and the direct lightning
float compute_lighting(t_dist *d, t_scene scene, t_vector *ray, t_dist *shadow)
{
    float       i;
    float       n_dot_l;
    t_vector    *l;

	i = scene.ambi_light.ratio; //The ambient lightning is the ground value for that ratio
    l = subtract_vec(scene.light.coordinates, d->p); //vector between the light source and the point
    n_dot_l = dot_prod_vec(d->n, l); //n is the normal vector in that point
	same_point(ray, d, scene, shadow);
    if (n_dot_l > 0) // if (n_dot_l > 0 && same_point(ray, d, scene, shadow)) // if n_dot_l is not posiive we're on the not light side of an object
        i += scene.light.brightness * n_dot_l/(len_vec(d->n) * len_vec(l));
    ft_free(l);
    if (i > 1) // the ratio can only be 1 max
        return (1);
    return (i);
}

void	init_dist(t_dist *dist)
{
	dist->min_dist = 0;
	dist->dist = 0;
	dist->closest_col = NULL;
	dist->p = NULL;
	dist->n = NULL;
	dist->light = 0;
}

static void	draw_sphere(t_scene scene, t_vector *ray, t_dist *d)
{
	t_sphere *sphere;

	while (scene.sphere)
	{
		sphere =  scene.sphere->content;
		d->dist = sphere_intersect(&scene.camera, ray, sphere);
		if (ft_compare_float(d->dist, 0) == 0 && (ft_f_less_f(d->dist, d->min_dist) || ft_compare_float(d->min_dist, 0) == 1))
		{
			d->min_dist = d->dist;
			if (d->p)
			{
				ft_free(d->p);
				ft_free(d->n);
			}
			d->p = scalar_multi(ray, d->min_dist);
			d->n = subtract_vec(d->p, sphere->center);
			norm_vec(d->n);
			// d->light = compute_lighting(d->p, d->n, scene.light, scene.ambi_light);
			// if (d->closest_col != NULL)
			// 	ft_free(d->closest_col);
			// d->closest_col = scalar_multi_colors(sphere->colors, d->light);
			// free(d->p);
			// free(d->n);
			d->closest_col = sphere->colors;
		}
		scene.sphere = scene.sphere->next;
	}
}

static void	draw_plane(t_scene scene, t_vector *ray, t_dist *d)
{
	t_plane *plane;

	while (scene.plane)
	{
		plane = scene.plane->content;
		d->dist = plane_intersect(plane, &scene.camera, ray);
		if (ft_compare_float(d->dist, 0) == 0 && (ft_f_less_f(d->dist, d->min_dist) || ft_compare_float(d->min_dist, 0) == 1))
		{
			d->min_dist = d->dist;
			if (d->p)
			{
				ft_free(d->n);
				ft_free (d->p);
			}
			d->p = scalar_multi(ray, d->min_dist);
			d->n = scalar_multi(plane->orientation, 1);
			//d->light = compute_lighting(d->p, d->n, scene.light, scene.ambi_light);
			// if (d->closest_col != NULL)
			// 	ft_free(d->closest_col);
			// d->closest_col = scalar_multi_colors(plane->colors, d->light);
			d->closest_col = plane->colors;
		}
		scene.plane = scene.plane->next;
	}
}

static void draw_cylinder(t_scene scene, t_vector *ray, t_dist *d)
{
	t_cylinder	*cylinder;
	t_dist		*p;

	(void)ray;
	while (scene.cylinder)
	{
		cylinder = scene.cylinder->content;
		p = cylinder_intersect(&scene.camera, ray, cylinder);
		d->dist = p->dist;
		if (ft_compare_float(d->dist, 0) == 0 && (ft_f_less_f(d->dist, d->min_dist) || ft_compare_float(d->min_dist, 0) == 1))
		{
			d->min_dist = d->dist;
			d->n = p->n;
			d->p = p->p;
			// if (d->closest_col)
			// 	ft_free(d->closest_col);
			// printf("\n\n%f %f %f\n", d->n->x, d->n->y, d->n->z);
			// exit(1);
			//d->closest_col = scalar_multi_colors(p.colors, 1);
			d->closest_col = cylinder->colors;
		}
		ft_free(p);
		scene.cylinder = scene.cylinder->next;
	}
}

//This function should work exactly like the raytracing with objects looking from the camera.
// First we create a new camera object, that is at the place of the lightning
void	get_shadow(t_scene scene, t_dist *d, t_dist *shadow, t_vector *ray)
{
	t_vector	*temp;
	t_vector	*point;

	temp = scalar_multi(ray, d->min_dist); // calculating the vector pointing from the camera to the closest seen point of an object
	point = add_vec(temp, scene.camera.origin); //adding this to the camera results in the actual point
	ft_free (temp);
	scene.camera.origin = scene.light.coordinates; // The new camera resides at the place of the light
	scene.camera.fov = 90; //doesn't really matter
	scene.camera.direction = subtract_vec(point, scene.light.coordinates); //looking in the direction of the point
	norm_vec(scene.camera.direction);
	// now do the same thing as for the original raytracing, but with the new camera and shadow
	if (scene.sphere)
		draw_sphere(scene, scene.camera.direction, shadow);
	if (scene.plane)
		draw_plane(scene, scene.camera.direction, shadow);
	if (scene.cylinder)
		draw_cylinder(scene, scene.camera.direction, shadow);
	ft_free(point);
	ft_free (scene.camera.direction);
	//printf("\n\n%f %f\n", d->min_dist, shadow->min_dist);
}

//get_color_sphere - gives the color of the background or the one of the sphere back, look into it, to adapt to other figures
// also keep track of the closest object up to date, to know, which pixel to actually put in the end
// Added the get shadow function
// Additionally, now, the adding of the ambient light is done in this function, the color that gets stored in closest_col is only the one of the closest object
// The vectors n and p, needed to calculate the lighting, are also stored in t_dist(d)
int	get_color(t_scene scene, t_vector *ray)
{
	t_dist *d;
	t_dist	*shadow;
	int color;

	d = malloc(sizeof(t_dist));
	init_dist(d);
	shadow = malloc(sizeof(t_dist)); //--->malloc Abfang??
	init_dist(shadow);
	if (scene.sphere)
		draw_sphere(scene, ray, d);
	if (scene.plane)
		draw_plane(scene, ray, d);
	if (scene.cylinder)
		draw_cylinder(scene, ray, d);
	if (d->min_dist)
	{
		get_shadow(scene, d, shadow, ray); //shadow is a t_dist pointer, and should now have the shortest direction to any object stored in min_dist
		d->light = compute_lighting(d, scene, ray, shadow);
		d->closest_col = scalar_multi_colors(d->closest_col, d->light);
		color = create_rgb(d->closest_col[0], d->closest_col[1],
							   d->closest_col[2]);
	}
	else
		color = create_rgb(0, 0, 0);
	free(d->closest_col);
	free(d);
	ft_free (shadow);
	return (color);
}

void	put_scene(t_scene scene, t_graphic *graphic)
{
    t_draw *pic;

    if (scene.ambi_light.ratio == 0)
        simple_error();
    if (graphic->zoom == 0)
        simple_error();
    pic = malloc(sizeof(t_draw));
    pic->mlx_y = 0;
    pic->y_angle = HEIGHT / 2 + (scene.camera.direction->y * HEIGHT / 2.0f);
    while (pic->y_angle > ((-1 * HEIGHT / 2) + (scene.camera.direction->y * HEIGHT / 2.0f)))
    {
        pic->y_ray = pic->y_angle * scene.vp.y_pix + scene.camera.origin->y;
        pic->x_angle = (-1 * WIDTH / 2) + (scene.camera.direction->x * WIDTH / 2.0f);
        pic->mlx_x = 0;
        while (pic->x_angle < WIDTH / 2 + (scene.camera.direction->x * WIDTH / 2.0f))
        {
            pic->x_ray = pic->x_angle * scene.vp.x_pix + scene.camera.origin->x;
            pic->ray = new_vector(pic->x_ray, pic->y_ray, scene.camera.direction->z);
            norm_vec(pic->ray);
			pic->color = get_color(scene, pic->ray);
            put_pix_to_image(graphic, pic->color, pic->mlx_x, pic->mlx_y);
            free(pic->ray);
            pic->x_angle++;
            pic->mlx_x++;
        }
        pic->y_angle--;
        pic->mlx_y++;
    }
    free(pic);
}
