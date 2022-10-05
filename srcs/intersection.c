#include "minirt.h"

//why are you even computing d2? It's good for nothing?
// maybe better use float compares
static float check_discr(float discr, float b)
{
    float		d1;
    float		d2;

    if (discr < 0)
        return (0);
    if (discr == 0)
    {
        d1 = -1 * b / 2 * 1;
        d2 = d1;
    }
    else
    {
        d1 = (-1 * b - sqrt(discr)) / 2;
        d2 = (-1 * b + sqrt(discr)) / 2;
        if (d1 < 0)
            d1 = d2; // inside the sphere
    }
    if (d1 > 0)
        return (d1);
    return (0);
}

/*
b^2  - 4ac
a = 1;
*/

float sphere_intersect(t_camera *cam, t_vector *ray, t_sphere *sphere) // + return distance + compare distance 
{
    t_vector	*l;
    float		d1;
    float 		b;
    float		c;
    float		discr;

    l = subtract_vec(cam->origin, sphere->center); //Gibt Abstand Kamera, Mittelpunkt Kugel - beware, ray ist ein Vektor, wir stellen aus vektor und Punkt erst einmal Geradengleichung auf
    b = 2 * (dot_prod_vec(ray, l));
    c = dot_prod_vec(l, l) - pow((sphere->diameter / 2), 2);
    discr = pow(b, 2) - 4 * 1 * c; //diskriminante, ray ist norminalisiert
    free(l);
    d1 = check_discr(discr, b);
    if (d1)
        return (d1);
    return (0);
}

/* pl->coordinates - Stuetzpunkt;
pl->orientation - Normalvektor = (a, b, c)
ax + cy + cz = d
Berechne d

     // cam + (rx, ry, rz) * t
 */
float plane_intersect(t_plane *pl, t_camera *cam, t_vector *ray)
{
    float	d;
    float	r;

    d = dot_prod_vec(pl->coordinates, pl->orientation);
    r = (d - dot_prod_vec(cam->origin, pl->orientation)) / dot_prod_vec(ray, pl->orientation);
    if (r <= 0)
        return (0);
    return (r);
}
