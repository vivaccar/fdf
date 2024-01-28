/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 09:53:19 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/28 16:01:04 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*init_map(void)
{
	t_map	*map;

	map = NULL;
	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		ft_error("INIT_MAP_ERROR\n");
	map->heigth = 0;
	map->width = 0;
	map->default_color = 1;
	map->high = INT_MIN;
	map->low = INT_MAX;
	return (map);
}

t_fdf	*init_fdf(t_map *map)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (fdf == NULL)
		ft_error("INIT_FDF_ERROR\n");
	fdf->mlx = mlx_init(fdf->mlx);
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "Fdf");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel),
			&(fdf->line_length), &(fdf->endian));
	fdf->map = map;
	return (fdf);
}

int	get_zoom(t_fdf *fdf)
{
	int	v1;
	int	v2;

	v1 = HEIGHT / fdf->map->heigth / 3;
	v2 = WIDTH / fdf->map->width / 3;
	if (v1 < 1 || v2 < 1)
		return (1);
	if (v1 > v2)
		return (v2);
	return (v1);
}

int	get_scale(int zoom)
{
	if (zoom / 2 <= 2)
		return (1);
	else 
		return (zoom / 2);
}

t_proj	*init_proj(t_fdf *fdf)
{
	t_proj	*proj;

	proj = (t_proj *)malloc(sizeof(t_proj));
	if (proj == NULL)
		ft_error("INIT_PROJ_ERROR\n");
	proj->plus_x = 0;
	proj->plus_y = 0;
	proj->zoom = get_zoom(fdf);
	printf("\n zoom: %i", proj->zoom);
	proj->scale = 1;
	proj->cos = 0.523599;
	proj->sin = 0.523599;
	proj->gamma = 0;
	proj->alpha = 0;
	proj->view = 1;
	proj->default_color = WHITE;
	return (proj);
}
