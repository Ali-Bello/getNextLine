/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderraj <aderraj@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 09:19:14 by aderraj           #+#    #+#             */
/*   Updated: 2023/12/08 09:19:24 by aderraj          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if ((dst != src))
	{
		while (i < n)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;

	if (!s1 || !*s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	ptr = malloc(len * sizeof(char));
	if (!ptr)
		return (NULL);
	return ((char *)ft_memcpy(ptr, s1, len));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	sub_len;
	size_t	src_len;

	if (!s)
		return (NULL);
	sub_len = 0;
	if (start <= ft_strlen(s))
	{
		src_len = ft_strlen(s + start);
		sub_len = ((src_len >= len) * len) + ((src_len < len) * src_len);
	}
	ptr = malloc(sizeof(char) * (sub_len + 1));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s + start, sub_len);
	ptr[sub_len] = 0;
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	size_t	len2;
	char	*ptr;

	if (!s1 || !s2)
	{
		if (s1)
			return (s1);
		else if (s2)
			return (ft_strdup(s2));
		else
			return (NULL);
	}
	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (len + len2 + 1));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, len);
	ft_memcpy(ptr + len, s2, len2);
	free(s1);
	ptr[len + len2] = 0;
	return (ptr);
}
