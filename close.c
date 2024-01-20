/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:57:55 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/20 17:42:42 by vivaccar         ###   ########.fr       */
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
	mlx_destroy_display(fdf->mlx);
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit (1);
}

void	move_img(t_fdf *fdf, int keycode)
{
	if (keycode == XK_Right)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		draw_img(fdf, 10, 0, 0);
	}
	else if (keycode == XK_Left)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		draw_img(fdf, -10, 0, 0);
	}
	else if (keycode == XK_Up)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		draw_img(fdf, 0, -10, 0);
	}
	else if (keycode == XK_Down)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		draw_img(fdf, 0, 10, 0);
	}
	else if (keycode == XK_space)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		draw_img(fdf, 0, 0, 1);
	}
	else
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
		draw_img(fdf, 0, 0, -1);
	}
}

int	keyup(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		exit_esc(fdf);
	else if (keycode == k_right || keycode == k_left || keycode == k_up || keycode == k_down || keycode == k_space || keycode == k_p)
		move_img(fdf, keycode);
	return (0);
}

