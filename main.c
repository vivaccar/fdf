/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:19:15 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/07 20:31:22 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_color(int y, int x, t_data *screen, t_map **map)
{
	if (map[y][x].z > 0)
		mlx_pixel_put(screen->mlx, screen->win, x * (screen->x / 25), y * (screen->y / 25), 0x00FF00);
}

void	draw_map(t_data *screen, t_map **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (x < 19)
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
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		exit(1);
	}
	return (0);
}

void	open_window(t_map **map)
{
	(void)	map;
	t_data	screen;

	screen.x = 700;
	screen.y = 460;
	screen.mlx = mlx_init();
	screen.win = mlx_new_window(screen.mlx, screen.x, screen.y, "FdF");
	draw_map(&screen, map);
	mlx_key_hook(screen.win, keyup, &screen);
	mlx_loop(screen.mlx);
}

int	main(int argc, char *argv[])
{
	t_map	**map;
	
	if (argc != 2)
		return (0);
	map = read_map(argv[1]);
	open_window(map);
	return (0);
/* 	int		fd;
	char	*line;
	
	line = NULL;
	fd = open(argv[1], O_RDONLY, 0);
	line = get_next_line(fd);
	printf("%s", line); */
}