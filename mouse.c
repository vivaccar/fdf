/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:01:29 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/25 10:12:29 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	press_mouse(int button, int x, int y, void *param)
{
	t_fdf *fdf;
	
	(void)x;
	(void)y;
	fdf = (t_fdf *)param;
	if (button == 1)
		fdf->mouse = 1;
	return (0);
}

int	release_mouse(int button, int x, int y, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	fdf->mouse = 0;
	return (0);
}