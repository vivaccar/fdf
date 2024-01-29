/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:04:15 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/29 18:34:13 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	move_img(t_fdf *fdf, int keycode)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (keycode == K_RIGHT)
		fdf->proj->plus_x += 10;
	else if (keycode == K_LEFT)
		fdf->proj->plus_x -= 10;
	else if (keycode == K_UP)
		fdf->proj->plus_y -= 10;
	else
		fdf->proj->plus_y += 10;
	draw_img(fdf, fdf->proj);
}

void	move_scale(t_fdf *fdf, int keycode)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (keycode == K_N)
		fdf->proj->scale++;
	else if (keycode == K_M)
		fdf->proj->scale--;
	if (fdf->proj->scale < 0)
		fdf->proj->scale = 0;
	draw_img(fdf, fdf->proj);
}

void	zoom_img(t_fdf *fdf, int keycode)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (keycode == K_Z)
		fdf->proj->zoom += 1;
	else
		fdf->proj->zoom -= 1;
	if (fdf->proj->zoom < 1)
		fdf->proj->zoom = 1;
	draw_img(fdf, fdf->proj);
}

void	rotate_img(t_fdf *fdf, int keycode)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (keycode == K_W)
		fdf->proj->rotate += 0.2;
	else if (keycode == K_A)
		fdf->proj->z_axis += 0.2;
	else if (keycode == K_S)
		fdf->proj->rotate -= 0.2;
	else if (keycode == K_D)
		fdf->proj->z_axis -= 0.2;
	draw_img(fdf, fdf->proj);
}

void	change_color(t_fdf *fdf, int keycode)
{
	(void) keycode;
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (fdf->proj->default_color == WHITE)
		fdf->proj->default_color = RED;
	else if (fdf->proj->default_color == RED)
		fdf->proj->default_color = GREEN;
	else if (fdf->proj->default_color == GREEN)
		fdf->proj->default_color = BLUE;
	else
		fdf->proj->default_color = WHITE;
	draw_img(fdf, fdf->proj);
}
