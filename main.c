/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:19:15 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/18 14:23:49 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* int	keyup(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_display(data->mlx);
		mlx_destroy_window(data->mlx, data->win);
		return (0);
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

	pixel_size = 30;
	center_x = (fdf->x - (fdf->heigth * pixel_size)) / 2;
	center_y = (fdf->y - (fdf->width * pixel_size)) / 2;
	real_x = x * pixel_size + center_x;
	real_y = y * pixel_size + center_y;
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
		while (x < fdf.heigth)
		{
			if (x < fdf.heigth - 1)
				draw_line(get_points(x, y, &fdf), get_points(x + 1, y, &fdf), &fdf, map[y][x]);
			if (y < fdf.width - 1)
				draw_line(get_points(x, y, &fdf), get_points(x, y + 1, &fdf), &fdf, map[y][x]);
			x++;
		}
		y++;
	}
} */

int	main(int argc, char *argv[])
{
	t_coords	**coords;
	(void) 		argc;
	
	coords = read_file(argv[1]);
	int	i = 0;
	int	j;
	while (i < 11)
	{
		j = 0;
		while (j < 19)
		{
			printf("%i", coords[i][j].z);
			j++;
		}
		i++;
	}
}