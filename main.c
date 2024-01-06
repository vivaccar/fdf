/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:19:15 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/06 00:46:30 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
} */

typedef struct t_data
{
	void	*mlx;
	void	*win;
}			t_data;

int	keyup(int keycode, t_data *data)
{
	printf("Tecla: %d\n", keycode);
	if (keycode == 65307)
	{
		write(1, "BYE", 3);
		mlx_destroy_window(data->mlx, data->win);
		exit(1);
	}
	return (0);
}

int	main(void)
{
	t_data	screen;
	//t_data	img;
	//int		line = 500;
	//int		row	= 100;

	screen.mlx = mlx_init();
	screen.win = mlx_new_window(screen.mlx, 600, 420, "FdF");
	//img.img = mlx_new_image(mlx, 1920, 1080);
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//my_mlx_pixel_put(&img, 960, 540, 0x00FF00);
	//mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_key_hook(screen.win, keyup, &screen);
	mlx_loop(screen.mlx);
}


