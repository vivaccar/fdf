/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:19:15 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/06 22:06:00 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(int fd)
{
	int	lines;

	lines = 0;
	while (get_next_line(fd))
		lines++;
	return (lines);
}

void	read_map(char	*file_path)
{
	t_map	**map;
	int		lines;
	//int		words;
	int 	fd;

	fd = open(file_path, O_RDONLY, 0);
	lines = get_height(fd);
	//words = 
	map = (t_map **)malloc(sizeof(t_map *) * (lines));
	printf("%i", lines);
}

int	main(int argc, char *argv[])
{
	//char	**map;

	read_map(argv[1]);
	
	(void)	argc;
/* 	int		fd;
	char	*line;
	
	line = NULL;
	fd = open(argv[1], O_RDONLY, 0);
	line = get_next_line(fd);
	printf("%s", line); */
}