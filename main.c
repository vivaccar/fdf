/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:19:15 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/20 17:17:46 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	config_events(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 1L<<0, keyup, fdf);
	mlx_hook(fdf->win, 17, 0, close_window, fdf);
}

int	main(int argc, char *argv[])
{
	t_map		*map;
	t_fdf		*fdf;

	if (argc != 2)
		ft_error("INVALID_ARGUMENTS_NUMBER\n");
	map = init_map();
	map->coords = read_file(argv[1], map);
	printf("Width: %i, Heigth: %i", map->width, map->heigth);
	fdf = init_fdf(map);
	draw_img(fdf, 0, 0, 0);
	config_events(fdf);
	mlx_loop(fdf->mlx);
}