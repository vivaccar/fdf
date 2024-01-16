/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:19:15 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/16 12:31:22 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img->addr + (y * data->img->line_length + x * (data->img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	draw_color(int x, int y, t_data *fdf, int map)
{
	(void) map;
    if (map == 0)
        my_mlx_pixel_put(fdf, x, y, 0xFFFFFF);
    else
    	my_mlx_pixel_put(fdf, x, y, 0x0000FF);
}

void	draw_line(t_point f, t_point s, t_data *fdf, int map)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		error[2];

	delta.x = abs(s.x - f.x);
	delta.y = abs(s.y - f.y);
	sign.x = f.x < s.x ? 1 : -1;
	sign.y = f.y < s.y ? 1 : -1;
	error[0] = delta.x - delta.y;
	cur = f;
	while (cur.x != s.x || cur.y != s.y)
	{
		draw_color(cur.x, cur.y, fdf, map);
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

t_point	get_points(int x, int y, t_data *fdf)
{
	t_point points;
	int	pixel_size;
	int	center_x;
	int	center_y;
	int	real_x;
	int	real_y;	

	pixel_size = 10;
	center_x = (fdf->x - (fdf->rows * pixel_size)) / 2;
	center_y = (fdf->y - (fdf->lines * pixel_size)) / 2;
	real_x = x * pixel_size + center_x;
	real_y = y * pixel_size + center_y;

	printf("%i, %i", points.x, points.y);
	points.x = real_x;
	points.y = real_y;
	return (points);
}

void	draw_img(int **map, t_data fdf)
{
	int	x;
	int	y;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (x < fdf.rows)
		{
			if (x < fdf.rows - 1)
				draw_line(get_points(x, y, &fdf), get_points(x + 1, y, &fdf), &fdf, map[y][x]);
			if (y < fdf.lines - 1)
				draw_line(get_points(x, y, &fdf), get_points(x, y + 1, &fdf), &fdf, map[y][x]);
			x++;
		}
		y++;
	}
}

void	open_window(int **map, t_data fdf)
{	
	fdf.img = malloc(sizeof(t_img));
	fdf.x = 1500;
	fdf.y = 850;
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, fdf.x, fdf.y, "FdF");
	fdf.img->img = mlx_new_image(fdf.mlx, fdf.x, fdf.y);
	fdf.img->addr = mlx_get_data_addr(fdf.img->img, &fdf.img->bits_per_pixel, &fdf.img->line_length, &fdf.img->endian);
	draw_img(map, fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img->img, 0, 0);
	mlx_key_hook(fdf.win, keyup, &fdf);
	mlx_mouse_hook(fdf.win, mouse_instructions, &fdf);
	mlx_loop(fdf.mlx);
}

int	main(int argc, char *argv[])
{
	int		**map;
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