/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:44:09 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/20 17:43:21 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	draw_color(int x, int y, t_fdf *fdf, int altitude)
{	
		(void) altitude;
		
		my_mlx_pixel_put(fdf, x, y, 0x00FF00);
} 

void	draw_line(t_point f, t_point s, t_fdf *fdf, int altitude)
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
		draw_color(cur.x, cur.y, fdf, altitude);
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

t_point	get_points(int x, int y, t_fdf *fdf, t_plus plus)
{
	t_point points;
	int	pixel_size;
	int	center_x;
	int	center_y;
	int	real_x;
	int	real_y;	

	pixel_size = 22 + plus.zoom;
	center_x = (WIDTH - (fdf->map->width * pixel_size)) / 2;
	center_y = (HEIGHT - (fdf->map->heigth * pixel_size)) / 2;
	real_x = (x - y) * pixel_size + center_x;
	real_y = (x + y) * pixel_size / 2 + center_y;
	real_y -= fdf->map->coords[y][x].z * 2;
	points.x = real_x + plus.plus_x;
	points.y = real_y + plus.plus_y;
	return (points);
}

void	draw_img(t_fdf *fdf, int plus_x, int plus_y, int zoom)
{
	int				x;
	int				y;
	static t_plus	plus;

	plus.plus_x += plus_x;
	plus.plus_y += plus_y;
	plus.zoom += zoom;
	y = 0;
	while (y < fdf->map->heigth)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x < fdf->map->width - 1)
				draw_line(get_points(x, y, fdf, plus), get_points(x + 1, y, fdf, plus), fdf, fdf->map->coords[y][x].z);
			if (y < fdf->map->heigth - 1)
				draw_line(get_points(x, y, fdf, plus), get_points(x, y + 1, fdf, plus), fdf, fdf->map->coords[y][x].z);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}