/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmehlig <jmehlig@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:14:07 by kmorunov          #+#    #+#             */
/*   Updated: 2022/10/30 17:05:48 by jmehlig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	p_error(int fd)
{
	write(STDERR_FILENO, "Error: wrong number of arguments\n", 33);
	if (fd != -1)
		close(fd);
	exit(EXIT_FAILURE);
}

void	msg_error(char *msg, char **line_split, int fd)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(1, "\n", 1);
	if (line_split != NULL)
		ft_split_del(&line_split);
	if (fd != -1)
		close(fd);
	exit(EXIT_FAILURE);
}

void	m_error(int fd)
{
	write(STDERR_FILENO, mlx_strerror(mlx_errno),
		ft_strlen(mlx_strerror(mlx_errno)));
	write(STDERR_FILENO, "\n", 1);
	if (fd != -1)
		close(fd);
	exit(EXIT_FAILURE);
}

void	error(int fd)
{
	write(STDERR_FILENO, "Error: allocation failed\n", 25);
	if (fd != -1)
		close(fd);
	exit(EXIT_FAILURE);
}

/*
void	leaks(void)
{
	system("leaks miniRT");
}
*/