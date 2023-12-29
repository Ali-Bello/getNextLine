/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 21:56:02 by aderraj           #+#    #+#             */
/*   Updated: 2023/12/08 22:01:37 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		((unsigned char *)s)[i++] = 0;
}

int	line_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*line_extract(char **buffer)
{
	int		i;
	char	*line;
	char	*tmp;

	i = 0;
	if (!*buffer)
		return (NULL);
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	i += (*buffer)[i] == '\n';
	line = ft_substr(*buffer, 0, i);
	if (!line)
	{
		free(*buffer);
		return (NULL);
	}
	tmp = ft_strdup(*buffer + i);
	free(*buffer);
	*buffer = 0;
	if (tmp && *tmp)
		*buffer = ft_strdup(tmp);
	free(tmp);
	return (line);
}

int	read_check(int fd, char **buffer)
{
	if (read(fd, 0, 0) < 0)
	{
		if (*buffer && *(*buffer))
		{
			free(*buffer);
			*buffer = 0;
		}
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*tmp;
	ssize_t		bytes;

	if (fd < 0 || read_check(fd, &buffer[fd]))
		return (NULL);
	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, BUFFER_SIZE + 1);
	bytes = read(fd, tmp, BUFFER_SIZE);
	if (bytes)
	{
		while (!line_check(tmp) && bytes)
		{
			buffer[fd] = ft_strjoin(buffer[fd], tmp);
			ft_bzero(tmp, BUFFER_SIZE + 1);
			bytes = read(fd, tmp, BUFFER_SIZE);
		}
		if (line_check(tmp))
			buffer[fd] = ft_strjoin(buffer[fd], tmp);
	}
	free(tmp);
	return (line_extract(&buffer[fd]));
}
