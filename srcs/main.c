/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:19:15 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/29 15:28:27 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_map		*map;
	t_proj		*proj;
	t_fdf		*fdf;

	if (argc != 2)
		ft_error("INVALID_ARGUMENTS_NUMBER\n");
	map = init_map();
	map->coords = read_file(argv[1], map);
	if (!map->coords)
	{
		free(map);
		ft_error("INVALID_MAP\n");
	}
	fdf = init_fdf(map);
	proj = init_proj(fdf);
	fdf->proj = proj;
	draw_img(fdf, proj);
	config_events(fdf);
	mlx_loop(fdf->mlx);
}
