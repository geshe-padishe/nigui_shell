/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:46:27 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/31 16:50:48 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigd_handler1(int i)
{
	(void)i;
	write(1, "\n> ", 3);
}

void	sigd_handler2(int i)
{
	(void)i;
	write(1, "\b\b  \b\b", 6);
}

void	sig_pipehand(int i)
{
	(void)i;
	dprintf(2, "ERRNO = %d\n", errno);
	dprintf(2, "ERRNO = %d\n", errno);
	dprintf(2, "ERRNO = %d\n", errno);
}
