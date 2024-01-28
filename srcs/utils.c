/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 13:02:44 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/28 19:42:49 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(int fd)
{
	int		lines;
	char	*line;

	line = NULL;
	lines = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (lines);
}

int	cnt_words(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

void	ft_error(char *str)
{
	ft_putstr_fd(str, 1);
	exit (0);
}

int	get_sign(int a, int b)
{
	int	result;

	if (a < b)
		result = 1;
	else
		result = -1;
	return (result);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}
