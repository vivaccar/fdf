/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:58:46 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/29 18:49:59 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coords	**alloc_map(char *file_path)
{
	int			fd;
	int			x;
	int			y;
	char		*line;
	t_coords	**coords;

	fd = open(file_path, O_RDONLY, 0);
	if ((fd < 0) || (!(ft_strnstr(file_path, ".fdf", ft_strlen(file_path)))))
		return (NULL);
	line = get_next_line(fd);
	x = cnt_words(line, ' ');
	free(line);
	y = get_height(fd) + 1;
	coords = NULL;
	coords = (t_coords **)malloc(sizeof(t_coords *) * (y + 1));
	if (coords == NULL)
		ft_error("COORDS_INIT_ERROR\n");
	while (--y >= 0)
	{
		coords[y] = (t_coords *)malloc(sizeof(t_coords) * (x + 1));
		if (coords[y] == NULL)
			ft_error("COORDS_INIT_ERROR\n");
	}
	close(fd);
	return (coords);
}

int	get_color(char *line, t_map *map)
{
	char	**comma;
	int		color;

	if (!(ft_strchr(line, ',')))
		color = -1;
	else
	{
		if (map->default_color == 1)
			map->default_color = 0;
		comma = ft_split(line, ',');
		color = ft_atoi_base(&comma[1][2], 16);
		free(comma[0]);
		free(comma[1]);
		free(comma);
	}
	return (color);
}

void	set_coords(t_coords **coords, char *line, int y, t_map *map)
{
	int		x;
	char	**splited_line;

	x = 0;
	splited_line = ft_split(line, ' ');
	while (splited_line[x])
	{
		coords[y][x].z = ft_atoi(splited_line[x]);
		coords[y][x].color = get_color(splited_line[x], map);
		free(splited_line[x]);
		x++;
	}
	free(splited_line);
}

t_coords	**read_file(char *file_path, t_map *map)
{
	t_coords	**coords;
	int			fd;
	char		*line;
	int			y;

	coords = alloc_map(file_path);
	if (coords == NULL)
		return (NULL);
	fd = open(file_path, O_RDONLY, 0);
	if (fd < 0 || coords == NULL)
		return (NULL);
	y = 0;
	line = get_next_line(fd);
	map->width = cnt_words(line, ' ');
	while (line != NULL)
	{
		set_coords(coords, line, y, map);
		y++;
		free(line);
		line = get_next_line(fd);
	}
	map->heigth = y;
	coords[y] = NULL;
	free(line);
	return (coords);
}
