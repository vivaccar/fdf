/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:58:46 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/07 22:41:22 by vivaccar         ###   ########.fr       */
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

t_map	**alloc_map(char *file_path, t_data *fdf)
{
	int		fd;
	int		x;
	int 	y;
	char	*line;
	t_map	**map;

	fd = open(file_path, O_RDONLY, 0);
	line = get_next_line(fd);
	x = cnt_words(line, ' ');
	free(line);
	y = get_height(fd) + 1;
	fdf->lines = y;
	fdf->rows = x;
	map = (t_map **)malloc(sizeof(t_map *) * (y + 1));
	y--;
	while (y >= 0)
	{
		map[y] = (t_map *)malloc(sizeof(t_map) * x + 1);
		y--;
	}
	close(fd);
	return (map);
}

void	set_map(t_map **map, char *line, int y)
{
	int		x;
	char	**splited_line;

	x = 0;
	splited_line = ft_split(line, ' ');
	while (splited_line[x])
	{
		map[y][x].x = x;
		map[y][x].y = y;
		map[y][x].z = ft_atoi(splited_line[x]);
		free(splited_line[x]);
		x++;
	}
}

t_map	**read_map(t_data *fdf, char *file_path)
{
	t_map	**map;
	int		fd;
	char	*line;
	int		y;

	map = alloc_map(file_path, fdf);
	fd = open(file_path, O_RDONLY, 0);
	y = 0;
	line = get_next_line(fd);
	//int	cw = cnt_words(line, ' ');
	while (line != NULL)
	{
		set_map(map, line, y);
		y++;
		free(line);
		line = get_next_line(fd);
	}
	map[y] = NULL;
	free(line);
/* 	//return (map);
	int	j;
	int k = 0;
	while (k < y)
	{
		j = 0;
		while (j < cw)
		{
			printf("%3d", map[k][j].z);
			j++;
		}
		printf("\n");
		k++;
	} */
	return (map);
}