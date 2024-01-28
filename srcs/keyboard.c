/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:04:15 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/28 16:22:00 by vivaccar         ###   ########.fr       */
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

void	reset_img(t_fdf *fdf, int keycode)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (keycode == XK_p)
		fdf->proj->view = 0;
	else
		fdf->proj->view = 1;
	fdf->proj->plus_x = 0;
	fdf->proj->plus_y = 0;
	fdf->proj->zoom = get_zoom(fdf);
	fdf->proj->scale = 1;
	fdf->proj->cos = 0.523599;
	fdf->proj->sin = 0.523599;
	fdf->proj->gamma = 0;
	fdf->proj->alpha = 0;
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
		fdf->proj->alpha += 0.2;
	else if (keycode == K_A)
		fdf->proj->gamma += 0.2;
	else if (keycode == K_S)
		fdf->proj->alpha -= 0.2;
	else if (keycode == K_D)
		fdf->proj->gamma -= 0.2;
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

int	keyup(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		exit_esc(fdf);
	else if (keycode == K_RIGHT || keycode == K_LEFT
		|| keycode == K_UP || keycode == K_DOWN)
		move_img(fdf, keycode);
	else if (keycode == K_Z || keycode == K_X)
		zoom_img(fdf, keycode);
	else if (keycode == K_M || keycode == K_N)
		move_scale(fdf, keycode);
	else if (keycode == K_R || keycode ==  K_P || keycode == K_I)
		reset_img(fdf, keycode);
	else if (keycode == K_W || keycode == K_A
		|| keycode == K_S || keycode == K_D)
		rotate_img(fdf, keycode);
	else if (keycode == K_SPACE)
		change_color(fdf, keycode);
	return (0);
}
