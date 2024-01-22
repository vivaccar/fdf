/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinivaccari <vinivaccari@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:57:55 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/22 11:37:05 by vinivaccari      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit (1);
	return (0);
}
void	exit_esc(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit (1);
}

void	move_img(t_fdf *fdf, int keycode)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (keycode == k_right)
		fdf->proj->plus_x += 10;
	else if (keycode == k_left)
		fdf->proj->plus_x -= 10;
	else if (keycode == k_up)
		fdf->proj->plus_y -= 10;
	else if (keycode == k_down)
		fdf->proj->plus_y += 10;
	else if (keycode == k_x)
		fdf->proj->zoom -= 3;
	else
		fdf->proj->zoom += 3;
	if (fdf->proj->zoom < 1)
		fdf->proj->zoom = 1;
	draw_img(fdf, fdf->proj);
}

void	move_scale(t_fdf *fdf, int keycode)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (keycode == k_n)
		fdf->proj->scale++;
	else if (keycode == k_m)
		fdf->proj->scale--;
	if (fdf->proj->scale <= 2)
		fdf->proj->scale = 2;
	draw_img(fdf, fdf->proj);
}

int	keyup(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		exit_esc(fdf);
	else if (keycode == k_right || keycode == k_left || keycode == k_up || keycode == k_down || keycode == k_z || keycode == k_x)
		move_img(fdf, keycode);
	else if (keycode == k_m || keycode == k_n)
		move_scale(fdf, keycode);
	return (0);
}

