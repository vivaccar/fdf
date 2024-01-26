/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:20:15 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/25 11:09:41 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(int *y, int *z, double alpha)
{
	int previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

void	rotate_y(int *x, int *z, double beta)
{
	int previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}
void	rotate_z(int *x, int *y, double gamma)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

void	iso(int *x, int *y, int z)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

t_point	get_points(int x, int y, t_fdf *fdf, t_proj *proj)
{
	t_point	points;
		
	points.x = x * proj->zoom;
	points.y = y * proj->zoom;
	points.x -= (fdf->map->width * proj->zoom) / 2;
	points.y -= (fdf->map->heigth * proj->zoom) / 2;
	rotate_x(&points.y, &fdf->map->coords[y][x].z, proj->alpha);
	rotate_y(&points.x, &fdf->map->coords[y][x].z, proj->beta);
	rotate_z(&points.x, &points.y, proj->gamma);
	if (1)
		iso(&points.x, &points.y, fdf->map->coords[y][x].z);
	points.x += WIDTH / 2;
	points.y += (HEIGHT + fdf->map->heigth * proj->zoom) / 3;
	return (points);
}