#include "minirt.h"

//free in the errors!!!!

void	simple_error_free(t_scene *scene, char **split_line, int fd)
{
	close(fd);
	if (split_line)
		ft_split_del(&split_line);
	free_scene(&scene);
	simple_error();
}

void	text_error_free(char *str, t_scene *scene, char **split_line, int fd)
{
	close (fd);
	if (split_line)
		ft_split_del(&split_line);
	free_scene(&scene);
	text_error(str);
}

void	simple_error(void)
{
	// system("leaks minirt");
	write(2, "\e[;31mError\n\e[;29m", 20);
	exit(1);
}

void	text_error(char *str)
{
	// system("leaks minirt");
	write(2, "\e[;31mError\n", 12);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

void	error_exit(int code)
{
	if (code == -1)
		write(STDERR_FILENO, "Unable to allocate memory\n", 26);
	exit(code);
}
