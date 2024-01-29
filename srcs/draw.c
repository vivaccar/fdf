/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 14:44:09 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/29 21:09:39 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	draw_color(int x, int y, t_fdf *fdf, t_coords coords)
{
	int	color;

	color = fdf->proj->default_color;
	if ((x > 0 && x < WIDTH) && (y > 0 && y < HEIGHT))
	{
		if (fdf->map->default_color == 1)
		{
			if (coords.z == 0)
				my_mlx_pixel_put(fdf, x, y, color);
			else
				my_mlx_pixel_put(fdf, x, y, color - 80);
		}
		else
		{
			if (coords.color != -1)
				my_mlx_pixel_put(fdf, x, y, coords.color);
			else
				my_mlx_pixel_put(fdf, x, y, WHITE);
		}
	}
}

void	draw_line(t_point f, t_point s, t_fdf *fdf, t_coords coords)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		error[2];

	delta = (t_point){ft_abs(s.x - f.x), ft_abs(s.y - f.y)};
	sign.x = get_sign(f.x, s.x);
	sign.y = get_sign(f.y, s.y);
	error[0] = delta.x - delta.y;
	cur = f;
	while (cur.x != s.x || cur.y != s.y)
	{
		draw_color(cur.x, cur.y, fdf, coords);
		error[1] = error[0] * 2;
		if (error[1] > -delta.y)
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
	t_point	points;
	int		prev_x;
	int		prev_y;

	points.x = x * proj->zoom;
	points.y = y * proj->zoom;
	points.x -= (fdf->map->width * proj->zoom) / 2;
	points.y -= (fdf->map->heigth * proj->zoom) / 2;
	rotate_z(&points.x, &points.y, proj->z_axis);
	prev_x = points.x;
	prev_y = points.y;
	if (proj->view == 1)
	{
		points.x = (prev_x - prev_y) * cos(0.523599);
		points.y = - (fdf->map->coords[y][x].z * proj->scale)
			+ (prev_x + prev_y) * sin(0.523599 + proj->rotate);
	}
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
				draw_line(get_points(x, y, fdf, proj), get_points(x + 1, y,
						fdf, proj), fdf, fdf->map->coords[y][x]);
			if (y < fdf->map->heigth - 1)
				draw_line(get_points(x, y, fdf, proj), get_points(x, y + 1,
						fdf, proj), fdf, fdf->map->coords[y][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	put_events(fdf);
}
