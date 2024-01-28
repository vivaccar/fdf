/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:57:55 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/28 20:13:46 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_coords(t_coords **coords, t_map *map)
{
	int	i;

	if (coords != NULL)
	{
		i = 0;
		while (i < map->heigth) 
		{
			free(coords[i]);
			i++;
		}
		free(coords);
	}
}

int	close_window(t_fdf *fdf)
{
	free_coords(fdf->map->coords, fdf->map);
	free(fdf->map);
	free(fdf->proj);
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	free(fdf);
	exit (0);
	return (0);
}

void	exit_esc(t_fdf *fdf)
{
	free_coords(fdf->map->coords, fdf->map);
	free(fdf->map);
	free(fdf->proj);
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	free(fdf);
	exit (0);
}
