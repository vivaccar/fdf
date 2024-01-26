/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:57:55 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/25 10:04:44 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit (1);
	return (0);
}
void	exit_esc(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->win);
	exit (1);
}



