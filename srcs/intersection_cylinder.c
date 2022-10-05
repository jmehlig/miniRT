#include "minirt.h"

t_camera	*camera_project(t_camera *cam, t_cylinder *cylinder)
{
	t_camera	*camera_cpy;

	camera_cpy = malloc (sizeof(t_camera));
	camera_cpy->origin = ortho_project_in_plane(cam->origin, cylinder->orientation, cylinder->coordinates); //
	camera_cpy->direction = ortho_project_in_plane(cam->direction, cylinder->orientation, cylinder->coordinates); //
	return (camera_cpy);
}

t_vector	*ray_project(t_vector *ray, t_cylinder *cylinder, t_camera	*camera_cpy)
{
	t_vector	*ray_cpy;
	t_vector	*temp;

	ray_cpy = ortho_project_in_plane(ray, cylinder->orientation, cylinder->coordinates);
	temp = subtract_vec(ray_cpy, camera_cpy->origin);
	free(ray_cpy);
	ray_cpy = NULL;
	ray_cpy = scalar_multi(temp, 1 / len_vec(temp));
	free (temp);
	return (ray_cpy);
}

float	cylinder_circle(t_cylinder *cylinder, t_camera	*camera_cpy, t_vector *ray_cpy)
{
	t_sphere	*sphere;
	float		d1;

	sphere = malloc (sizeof(t_sphere));
	sphere->center = cylinder->coordinates;
	sphere->diameter = cylinder->diameter;
	d1 = sphere_intersect(camera_cpy, ray_cpy, sphere);
	free (sphere);
	return (d1);
}

// Ebene gegeben in Normalform, durch Normalenvektor und Ankerpunkt, Orthogonalprojektion eines Punktes in diese Ebene
// Was ist mit z == 0???
t_vector	*ortho_project_in_plane(t_vector *in, t_vector *normal_vec, t_vector *point)
{
	t_vector *project;
	t_vector *result;
	float	temp;

	project = subtract_vec(in, point);
	temp = dot_prod_vec(project, normal_vec);
	free (project);
	project = NULL;
	temp = temp / (dot_prod_vec(normal_vec, normal_vec));
	project = new_vector(temp * normal_vec->x, temp * normal_vec->y, temp * normal_vec->z);
	result =  subtract_vec(in, project);
	free (project);
	return (result);
}

t_dist *cylinder_intersect(t_camera *cam, t_vector *ray, t_cylinder *cylinder) // + return distance + compare distance
{
	t_camera	*camera_cpy;
	t_vector	*temp;
	t_vector	*ray_cpy;
	//t_vector	*n = NULL;
	t_dist		*d;
	float		new;
	float		d1;

	d = malloc(sizeof(t_dist));
	if (!d)
		return NULL;
	init_dist(d);
	new = 0;
	camera_cpy = camera_project(cam, cylinder);
	ray_cpy = ray_project(ray, cylinder, camera_cpy);
	d1 = cylinder_circle(cylinder, camera_cpy, ray_cpy);
	if (d1)
	{
		temp = new_vector(camera_cpy->origin->x + ray_cpy->x * d1, camera_cpy->origin->y + ray_cpy->y * d1, camera_cpy->origin->z + ray_cpy->z * d1); //
		new = basis_change_back(temp, cylinder->orientation, ray, cylinder);
		d->n = subtract_vec(temp, cylinder->coordinates);
		norm_vec(d->n); //
		ft_free(temp);
	}
	if (new == 0) // check for top and bottom
	{
		if (d->n) 
			ft_free(d->n);
		d->n = scalar_multi(cylinder->orientation, 1);
		new = cylinder_caps('+', ray, cam, cylinder);
	}
	if (new == 0) // check for top and bottom
	{
		if (d->n)
			ft_free(d->n);
		d->n = scalar_multi(cylinder->orientation, -1);
		new = cylinder_caps('-', ray, cam, cylinder);
	}
	d->dist = new;
	if (d->p) // --->bedenke,das ist Schwachsinn und kreiert momentan Fehler
		ft_free (d->p);
	d->p = scalar_multi(ray, new);
	//p.colors = scalar_multi_colors(cylinder->colors, compute_lighting(temp, n, scene.light, scene.ambi_light));
	//free (temp);
	free (camera_cpy->origin);
	free (camera_cpy->direction);
	free (camera_cpy);
	free (ray_cpy);
	return (d);
}

float	basis_change_back(t_vector *point, t_vector *n, t_vector *ray, t_cylinder *cy)
{
    float		t;
    float		u;
    t_vector	*vec;

    u = 0;
    t = 0;
    if (n->x == 0 && ray->x != 0)
    {
        u = point->x / ray->x;
        if (n->y == 0)
            t = (ray->z * u - point->z) / n->z;
        else
            t = (ray->y * u - point->y) / n->y;
    }
    else if (n->x != 0)
    {
        t = (ray->x * point->y - ray->y *point->x) / (n->x + ray->x * n->y);
        u = (point->y + n->y * t) / ray->y;
    }
    vec = scalar_multi(ray, u);
    if (ft_f_less_f(fabs(t), fabs(cy->height) / 2) == 0)
        u = 0;
    else
        u = len_vec(vec);
    free(vec);
    return (u);
}

float	cylinder_caps(char loc, t_vector *ray, t_camera *cam, t_cylinder *cylinder)
{
    t_vector	*temp;
    t_vector	*ray_cpy;
    float		new;
    t_plane		*pl;

    pl = malloc(sizeof(t_plane));
    temp = scalar_multi(cylinder->orientation, cylinder->height / 2);
    if (loc == '+')
        pl->coordinates = new_vector(temp->x + cylinder->coordinates->x, temp->y + cylinder->coordinates->y, temp->z + cylinder->coordinates->z);
    else
        pl->coordinates = new_vector(temp->x - cylinder->coordinates->x, temp->y - cylinder->coordinates->y, temp->z - cylinder->coordinates->z);
    pl->orientation = cylinder->orientation;
    free(temp);
	temp = NULL;
    new = plane_intersect(pl, cam, ray);
    ray_cpy = scalar_multi(ray, new);
    temp = subtract_vec(ray_cpy, pl->coordinates);//
    if (fabs(len_vec(temp)) >= cylinder->diameter / 2)
        new = 0;
    free (pl->coordinates);
    free (pl);
    free (ray_cpy);
    free (temp);
    return (new);
}
