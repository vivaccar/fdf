/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:41:10 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/29 18:13:29 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(int *x, int *y, double z_axis)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(z_axis) - previous_y * sin(z_axis);
	*y = previous_x * sin(z_axis) + previous_y * cos(z_axis);
}

void	config_events(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 1L << 0, keyup, fdf);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
}
