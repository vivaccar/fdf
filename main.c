/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:19:15 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/15 11:54:10 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_color(int y, int x, t_data *screen, t_map **map)
{
    int pixel_size = 12;

    int center_x = (screen->x - (screen->rows * pixel_size)) / 2;
    int center_y = (screen->y - (screen->lines * pixel_size)) / 2;

    int real_x = x * pixel_size + center_x;
    int real_y = y * pixel_size + center_y;
	
    if (map[y][x].z == 0)
        mlx_pixel_put(screen->mlx, screen->win, real_x, real_y, 0xFF0000);
    else
        mlx_pixel_put(screen->mlx, screen->win, real_x, real_y, 0x00FF00);
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

int	mouse_instructions(int button, int x, int y, t_data *fdf)
{
	(void) fdf;
	if (button == 1)
	{
		printf("X: %i\nY: %i", x, y);
		exit(1);
	}
	return(0);
}

void	open_window(t_map **map, t_data fdf)
{
	fdf.x = 1500;
	fdf.y = 850;
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, fdf.x, fdf.y, "FdF");
	draw_map(&fdf, map);
	mlx_key_hook(fdf.win, keyup, &fdf);
	mlx_mouse_hook(fdf.win, mouse_instructions, &fdf);
	mlx_loop(fdf.mlx);
}

int	main(int argc, char *argv[])
{
	t_map	**map;
	t_data	fdf;
	
	if (argc != 2)
		return (0);
	map = read_map(&fdf, argv[1]);
	printf("rows: %i\nlines: %i\n", fdf.rows, fdf.lines);
	open_window(map, fdf);
	return (0);
/* 	int		fd;
	char	*line;
	
	line = NULL;
	fd = open(argv[1], O_RDONLY, 0);
	line = get_next_line(fd);
	printf("%s", line); */
}