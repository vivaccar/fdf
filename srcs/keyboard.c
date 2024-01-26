/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:04:15 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/26 12:09:42 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	else
		fdf->proj->plus_y += 10;
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
	fdf->proj->scale = get_scale(fdf->proj->zoom);
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
	if (keycode == k_z)
	{
		fdf->proj->zoom += 1;
		//fdf->proj->scale += get_scale(fdf->proj->zoom) / get_zoom(fdf);
	}
	else
	{
		fdf->proj->zoom -= 1;
		//fdf->proj->scale -= get_scale(fdf->proj->zoom) / get_zoom(fdf);	
	}
	if (fdf->proj->zoom < 1)
	{
		fdf->proj->zoom = 1;;
	}
	draw_img(fdf, fdf->proj);
}

void	rotate_img(t_fdf *fdf, int keycode)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (keycode == XK_w)
		fdf->proj->alpha += 0.2;
	else if (keycode == XK_a)
		fdf->proj->gamma += 0.2;
	else if (keycode == XK_s)
		fdf->proj->alpha -= 0.2;
	else if (keycode == XK_d)
		fdf->proj->gamma -= 0.2;
	draw_img(fdf, fdf->proj);
}

int	keyup(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
		exit_esc(fdf);
	else if (keycode == k_right || keycode == k_left || keycode == k_up || keycode == k_down)
		move_img(fdf, keycode);
	else if (keycode == k_z ||  keycode == k_x)
		zoom_img(fdf, keycode);
	else if (keycode == k_m || keycode == k_n)
		move_scale(fdf, keycode);
	else if (keycode == k_r || keycode == XK_p || keycode == XK_i)
		reset_img(fdf, keycode);
	else if (keycode == XK_w || keycode == XK_a || keycode == XK_s || keycode == XK_d)
		rotate_img(fdf, keycode);		
	return (0);
}