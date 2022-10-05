#include "minirt.h"

t_vector    *subtract_vec(t_vector *v1, t_vector *v2)
{
	t_vector    *result;

	result = new_vector(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
	return (result);
}

t_vector    *add_vec(t_vector *v1, t_vector *v2)
{
	t_vector    *result;

	result = new_vector(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
	return (result);
}

t_vector    *scalar_multiply_vec(float x, t_vector *v2)
{
	t_vector    *result;

	result = new_vector(x * v2->x, x * v2->y, x * v2->z);
	return (result);
}

float len_vec(t_vector *v)
{
	float   result; 

	result = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z)); //could have been sqrt(dot_prod_vec(v, v);)
	return (result);
}

// Skalarprodukt
float dot_prod_vec(t_vector *v1, t_vector *v2)
{
	float   result;

	result = (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
	return (result);
}

void    norm_vec(t_vector *v)
{
	float   length;

	length =  len_vec(v);
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

t_vector    *new_vector(float x, float y, float z)
{
	t_vector    *new_vector;

	new_vector = malloc(sizeof(t_vector));
	if (!new_vector)
		error_exit(-1);
	new_vector->x = x; 
	new_vector->y = y;
	new_vector->z = z;
	return (new_vector);
}

t_vector	*scalar_multi(t_vector *vec, float a)
{
	t_vector *new_vec;

	new_vec = malloc(sizeof(t_vector));
	if (!new_vec)
		error_exit(-1);
	new_vec->x = vec->x * a;
	new_vec->y = vec->y * a;
	new_vec->z = vec->z * a;
	return (new_vec);
}
