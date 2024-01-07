/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:19:15 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/07 23:12:59 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_color(int y, int x, t_data *screen, t_map **map)
{
	if (map[y][x].z == 0)
		mlx_pixel_put(screen->mlx, screen->win, x, y, 0xFF0000);
	if (map[y][x].z > 0)
		mlx_pixel_put(screen->mlx, screen->win, x, y, 0x0000FF);
}

void	draw_map(t_data *screen, t_map **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (x < screen->rows)
		{
			draw_color(y, x, screen, map);
			x++;
		}
		y++;
	}
}

int	keyup(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_display(data->mlx);
		mlx_destroy_window(data->mlx, data->win);
		exit(1);
	}
	return (0);
}

void	open_window(t_map **map, t_data fdf)
{
	fdf.x = 1100;
	fdf.y = 760;
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, fdf.x, fdf.y, "FdF");
	draw_map(&fdf, map);
	mlx_key_hook(fdf.win, keyup, &fdf);
	mlx_loop(fdf.mlx);
}

int	main(int argc, char *argv[])
{
	t_map	**map;
	t_data	fdf;
	
	if (argc != 2)
		return (0);
	map = read_map(&fdf, argv[1]);
	printf("%i", fdf.rows);
	open_window(map, fdf);
	return (0);
/* 	int		fd;
	char	*line;
	
	line = NULL;
	fd = open(argv[1], O_RDONLY, 0);
	line = get_next_line(fd);
	printf("%s", line); */
}