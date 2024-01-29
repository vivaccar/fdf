/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 18:35:44 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/29 18:36:00 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	else if (keycode == K_R || keycode == K_P || keycode == K_I)
		reset_img(fdf, keycode);
	else if (keycode == K_W || keycode == K_A
		|| keycode == K_S || keycode == K_D)
		rotate_img(fdf, keycode);
	else if (keycode == K_SPACE)
		change_color(fdf, keycode);
	return (0);
}

void	put_events(t_fdf *fdf)
{
	int	y;

	y = 20;
	mlx_string_put(fdf->mlx, fdf->win, 20,
		y, WHITE, "ZOOM: +Z  / -X");
	mlx_string_put(fdf->mlx, fdf->win, 20,
		y += 20, WHITE, "MOVE: up, down, right, left");
	mlx_string_put(fdf->mlx, fdf->win, 20,
		y += 20, WHITE, "ROTATE: W, A, S, D");
	mlx_string_put(fdf->mlx, fdf->win, 20,
		y += 20, WHITE, "RESET: R");
	mlx_string_put(fdf->mlx, fdf->win, 20,
		y += 20, WHITE, "Z HEIGHT: -M  /  +N");
	mlx_string_put(fdf->mlx, fdf->win, 20,
		y += 20, WHITE, "PARALLEL VIEW: P");
	mlx_string_put(fdf->mlx, fdf->win, 20,
		y += 20, WHITE, "ISOMETRIC VIEW: I");
	mlx_string_put(fdf->mlx, fdf->win, 20,
		y += 20, WHITE, "CHANGE COLOR: SPACE");
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
	fdf->proj->z_axis = 0;
	fdf->proj->rotate = 0;
	draw_img(fdf, fdf->proj);
}
