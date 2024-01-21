/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:53:19 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/21 17:48:21 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*init_map()
{
	t_map	*map;

	map = NULL;
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		ft_error("INIT_MAP_ERROR\n");
	map->heigth = 0;
	map->width = 0;
	return (map);
}

t_fdf	*init_fdf(t_map *map)
{
	t_fdf	*fdf;
	
	if (!(fdf = (t_fdf *)malloc(sizeof(t_fdf))))
		ft_error("INIT_FDF_ERROR\n");
	fdf->mlx = mlx_init(fdf->mlx);
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "Fdf");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel), &(fdf->line_length), &(fdf->endian));
	fdf->map = map;
	return (fdf);
}

t_proj	*init_proj()
{
	t_proj	*proj;

	proj = (t_proj *)malloc(sizeof(t_proj));
	proj->plus_x = 0;
	proj->plus_y = 0;
	proj->zoom = 0;
	return (proj);
}