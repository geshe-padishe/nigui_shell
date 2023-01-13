/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:32:02 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/13 06:12:14 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "miniparsing.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (len--)
		*ptr++ = (unsigned char)c;
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	ptr = malloc(size * count);
	if (!ptr)
		return (0);
	ft_memset(ptr, '\0', count * size);
	return (ptr);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;

	p_src = (unsigned char *)src;
	p_dest = (unsigned char *)dest;
	if (dest == src)
		return (dest);
	while (n--)
		*(p_dest++) = *(p_src++);
	return (dest);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	size;

	if (!s)
		return (0);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	if (ft_strlen(s + start) < len)
		size = ft_strlen(s + start);
	else
		size = len;
	p = malloc(sizeof(char) * (size + 1));
	if (!p)
		return (0);
	ft_memcpy(p, s + start, size);
	p[len] = '\0';
	return (p);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t			i;
	size_t			dst_size;
	size_t			src_size;

	dst_size = ft_strlen(dst);
	src_size = ft_strlen((char *)src);
	if (size <= dst_size)
		return (src_size + size);
	i = 0;
	while (src[i] && dst_size + i < size - 1)
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	return (dst_size + src_size);
}
