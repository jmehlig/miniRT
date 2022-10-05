#include "minirt.h"

//t_color			color_from_rgb(int r, int g, int b)
//{
//    t_color	color;
//
//    color.r = r;
//    color.g = g;
//    color.b = b;
//    return (color);
//}
//
//t_color	color_from_hex(int hex)
//{
//    t_color	tmp;
//
//    tmp.r = ((hex >> 16) & 0xFF);
//    tmp.g = ((hex >> 8) & 0xFF);
//    tmp.b = ((hex) & 0xFF);
//    return (tmp);
//}
//
//int	hex_from_color(t_color color)
//{
//    return (color.r * 65536 + color.g * 256 + color.b);
//}

int	*scalar_multi_colors(int *colors, float a)
{
	int *col;

	col = malloc(3 * sizeof(int));
	if(!col)
		return 0;
	col[0] = colors[0] * a;
	col[1] = colors[1] * a;
	col[2] = colors[2] * a;
	return (col);
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	put_pix_to_image(t_graphic *graphic, int color, int x, int y)
{
	char	*pixel;
	pixel = graphic->addr + (y * graphic->line_l + x * (graphic->bpp / 8));
	*(int *)pixel = color;
}
