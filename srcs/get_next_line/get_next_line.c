/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaccar <vivaccar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 10:58:10 by vivaccar          #+#    #+#             */
/*   Updated: 2024/01/28 17:27:27 by vivaccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_line(char *text)
{
	int		i;
	char	*line;

	i = 0;
	if (!text[i])
		return (NULL);
	while (text[i] && text[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (text[i] && text[i] != '\n')
	{
		line[i] = text[i];
		i++;
	}
	if (text[i] == '\n')
	{
		line[i] = text[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_delete(char *text)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (!text[i])
	{
		free(text);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(char) * (ft_strlen2(text) - i + 1));
	if (!rest)
		return (NULL);
	i++;
	j = 0;
	while (text[i])
		rest[j++] = text[i++];
	rest[j] = '\0';
	free(text);
	return (rest);
}

char	*ft_read(int fd, char *text)
{
	char	*buff;
	int		bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (!ft_strchr2(text, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			free(text);
			return (NULL);
		}
		buff[bytes] = '\0';
		text = ft_strjoin2(text, buff);
	}
	free(buff);
	return (text);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*text;

	if (fd == -1)
		free(text);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	text = ft_read(fd, text);
	if (!text)
		return (NULL);
	line = ft_line(text);
	text = ft_delete(text);
	return (line);
}
