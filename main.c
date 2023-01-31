/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:45:06 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/31 19:56:48 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_safe			g_vrac;

int	main(int ac, char **av, char **envp)
{
	t_dynarray	darr;
	int			ret;

	if (isatty(STDIN_FILENO) == 0)
		return (0);
	(void)av;
	(void)ac;
	g_vrac.status = 0;
	ft_memset(&darr, 0, sizeof(t_dynarray));
	signal(SIGINT, siginthandler);
	signal(SIGQUIT, SIG_IGN);
	ret = ft_readline(&darr, envp);
	return (ret);
}
