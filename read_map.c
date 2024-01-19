/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:58:46 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/19 09:28:20 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(int fd)
{
	int		lines;
	char	*line;

	line = NULL;
	lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (lines);
}

int	cnt_words(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

void	ft_error(char *str)
{
	ft_putstr_fd(str, 1);
	exit (1);
}

t_coords	**alloc_map(char *file_path)
{
	int			fd;
	int			x;
	int 		y;
	char		*line;
	t_coords	**coords;

	fd = open(file_path, O_RDONLY, 0);
	line = get_next_line(fd);
	x = cnt_words(line, ' ');
	free(line);
	y = get_height(fd) + 1;
	coords = NULL;
	if(!(coords = (t_coords**)malloc(sizeof(t_coords *) * (y + 1))))
		ft_error("COORDS_INIT_ERROR\n");
	y--;
	while (y >= 0)
	{
		if (!(coords[y] = (t_coords *)malloc(sizeof(t_coords) * (x + 1))))
			ft_error("COORDS_INIT_ERROR\n");
		y--;
	}
	close(fd);
	return (coords);
}

void	set_coords(t_coords **coords, char *line, int y)
{
	int		x;
	char	**splited_line;

	x = 0;
	splited_line = ft_split(line, ' ');
	while (splited_line[x])
	{
		coords[y][x].z = ft_atoi(splited_line[x]);
		coords[y][x].color = 0;
		free(splited_line[x]);
		x++;
	}
	free(splited_line);
}

t_coords	**read_file(char *file_path)
{
	t_coords	**coords;
	int			fd;
	char		*line;
	int			y;

	coords = alloc_map(file_path);
	if (coords == NULL)
		return (NULL);
	fd = open(file_path, O_RDONLY, 0);
	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		set_coords(coords, line, y);
		y++;
		free(line);
		line = get_next_line(fd);
	}
	coords[y] = NULL;
	free(line);
	return (coords);
}