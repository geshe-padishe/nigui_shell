/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhater <hkhater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 07:14:25 by hkhater           #+#    #+#             */
/*   Updated: 2022/12/22 07:15:06 by hkhater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniparsing.h"

static int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_alnumund(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}

int	is_redir(char c)
{
	return (c == '<' || c == '>');
}

int	is_operator(char c)
{
	return (is_redir(c) || c == '|');
}
