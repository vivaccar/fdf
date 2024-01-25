/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:44:09 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/25 09:55:36 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int 	get_default_color(t_fdf *fdf, t_coords coords)
{
	int	div;
	int color;

	color = 0x0000FF;
	if (coords.z == 0)
		return (0xFFFFFF);
	div = fdf->map->high / coords.z;
	if (div > fdf->map->high / 2)
		color = 0x0000FF;
	if (div > fdf->map->high / 3)
		color = 0x000FFF;
	return (color);
}

void	draw_color(int x, int y, t_fdf *fdf, t_coords coords)
{	
	if ((x > 0 && x < WIDTH) && (y > 0 && y < HEIGHT))
	{
		if (fdf->map->default_color == 1)
		{
			coords.color = get_default_color(fdf, coords);
			my_mlx_pixel_put(fdf, x, y, coords.color);
		}
		else
		{
			if (coords.color != -1)
				my_mlx_pixel_put(fdf, x, y, coords.color);
			else
				my_mlx_pixel_put(fdf, x, y, 0xFFFFFF);
		}
	}
} 

void	draw_line(t_point f, t_point s, t_fdf *fdf, t_coords coords)
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
		draw_color(cur.x, cur.y, fdf, coords);
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

t_point	get_points(int x, int y, t_fdf *fdf, t_proj *proj)
{
	t_point points;
	int	prev_x;
	int	prev_y;
	
	points.x = x * proj->zoom;
	points.y = y * proj->zoom;
	points.x -= (fdf->map->width * proj->zoom) / 2;
	points.y -= (fdf->map->heigth * proj->zoom) / 2;
	prev_x = points.x;
	prev_y = points.y;
	points.x = (prev_x - prev_y) * cos(0.523599);
	points.y = - (fdf->map->coords[y][x].z * proj->scale) + (prev_x + prev_y) * sin(0.523599);
	points.x += WIDTH / 2;
	points.y += (HEIGHT + fdf->map->heigth * (proj->zoom)) / 3;
	points.x += proj->plus_x;
	points.y += proj->plus_y;
	return (points);
}

void	draw_img(t_fdf *fdf, t_proj *proj)
{
	int				x;
	int				y;

	y = 0;
	while (y < fdf->map->heigth)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x < fdf->map->width - 1)
				draw_line(get_points(x, y, fdf, proj), get_points(x + 1, y, fdf, proj), fdf, fdf->map->coords[y][x]);
			if (y < fdf->map->heigth - 1)
				draw_line(get_points(x, y, fdf, proj), get_points(x, y + 1, fdf, proj), fdf, fdf->map->coords[y][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}