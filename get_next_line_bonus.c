/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenlafk <ybenlafk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:01:05 by ybenlafk          #+#    #+#             */
/*   Updated: 2022/11/09 11:49:24 by ybenlafk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extra(char	*res)
{
	char	*s;
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (res[i] == '\n')
		i++;
	if (i >= ft_strlen(res))
		return (free(res), NULL);
	s = malloc((ft_strlen(res) - i) + 1);
	if (!s)
		return (NULL);
	while (res[i])
		s[j++] = res[i++];
	s[j] = '\0';
	return (free(res), res = NULL, s);
}

char	*get_line(char	*res)
{
	int		i;
	char	*s;

	i = 0;
	if (!res[i])
		return (NULL);
	while (res[i] != '\n' && res[i])
		i++;
	s = malloc(i + 2);
	if (!s)
		return (NULL);
	i = 0;
	while (res[i] != '\n' && res[i])
	{
		s[i] = res[i];
		i++;
	}
	if (res[i] == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*res[OPEN_MAX];
	char		*p;
	char		*line;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!res[fd])
		res[fd] = ft_strdup("");
	p = malloc(BUFFER_SIZE + 1);
	if (!p)
		return (NULL);
	i = 1;
	while (!(ft_strchr(res[fd], '\n')) && i)
	{
		i = read(fd, p, BUFFER_SIZE);
		if (i < 0)
			return (free(res[fd]), free(p), res[fd] = NULL, NULL);
		p[i] = '\0';
		res[fd] = ft_strjoin(res[fd], p);
	}
	free(p);
	line = get_line(res[fd]);
	res[fd] = extra(res[fd]);
	return (line);
}
