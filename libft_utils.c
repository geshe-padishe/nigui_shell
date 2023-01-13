/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 08:06:23 by hkhater           #+#    #+#             */
/*   Updated: 2022/12/27 08:06:54 by hkhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"

static unsigned int	ft_count(int n)
{
	unsigned int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*p;
	char			sign;
	unsigned int	count;

	sign = '\0';
	if (n < 0)
		sign = '-';
	count = ft_count(n);
	p = malloc(sizeof(char) * (count + 1));
	if (!p)
		return (0);
	p[count] = '\0';
	while (count)
	{
		if (n < 0)
			p[--count] = -(n % 10) + '0';
		else
			p[--count] = (n % 10) + '0';
		n /= 10;
	}
	if (sign)
		p[count] = sign;
	return (p);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if ((s1[i] == '\0' || s2[i] == '\0'))
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	unquote_len(const char *str)
{
	int		i;
	size_t	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 0)
			len++;
		i++;
	}
	printf("unquote len is %ld\n", len);
	return (len);
}
