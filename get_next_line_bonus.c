/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skasmi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 21:29:36 by skasmi            #+#    #+#             */
/*   Updated: 2022/02/25 23:46:54 by skasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_rest(char *st)
{
	size_t	i;
	size_t	k;
	char	*rest;

	i = 0;
	while (st[i] != '\n' && st[i])
		i++;
	if (ft_strlen(st) == i)
	{
		free(st);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(char) * (ft_strlen(st) - i + 1));
	if (!rest)
		return (NULL);
	k = 0;
	while (st[i++])
	{
		rest[k] = st[i];
		k++;
	}
	rest[k] = '\0';
	free(st);
	return (rest);
}

char	*ft_line(char *str)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	if (str[0] == '\0')
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_read(char *str, int fd)
{
	char	*buff;
	int		s1;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	s1 = 1;
	while (!ft_strchr(str, '\n') && s1 != 0)
	{
		s1 = read(fd, buff, BUFFER_SIZE);
		if (s1 == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[s1] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[10240];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = ft_read(str[fd], fd);
	if (str[fd] == NULL )
		return (NULL);
	line = ft_line(str[fd]);
	str[fd] = ft_rest(str[fd]);
	return (line);
}
