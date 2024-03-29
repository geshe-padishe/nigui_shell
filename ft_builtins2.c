/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:46:17 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/28 01:20:20 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_tout *tout, char **args)
{
	int	i;

	if (!(args - 1) || !args[0])
		return (printf("exit\n"), ft_free_all(tout->darr, tout->lst,
				tout->pipefd, tout->nb_pipes), free(args - 1),
			exit(g_vrac.status), 1);
	if (args[0] && args[1])
	{
		if (ft_is_number(args[0]))
			return (free(args - 1), put_err(ARGS), 0);
		return (printf("exit\n"), num_arg(args - 1), ft_free_all(tout->darr,
				tout->lst, tout->pipefd, tout->nb_pipes),
			exit(2), 1);
	}
	if (!ft_is_number(args[0]))
		return (printf("exit\n"), num_arg(args - 1), ft_free_all(tout->darr,
				tout->lst, tout->pipefd, tout->nb_pipes),
			exit(2), 1);
	else
	{
		i = ft_ps_atoi(args[0]);
		return (printf("exit\n"), ft_free_all(tout->darr, tout->lst,
				tout->pipefd, tout->nb_pipes),
			free(args - 1), exit((unsigned char)i), i);
	}
}

int	ft_atoi_sign(char **nstr)
{
	int	sign;

	sign = 1;
	if (**nstr == '-' || **nstr == '+')
	{
		(*nstr)++;
		if (*(*nstr - 1) == '-')
			sign = -1;
	}
	return (sign);
}

int	ft_ps_atoi(char *nstr)
{
	long long	nbr;
	int			sign;

	nbr = 0;
	sign = ft_atoi_sign(&nstr);
	if (*nstr >= '0' && *nstr <= '9')
	{
		while (*nstr >= '0' && *nstr <= '9')
		{
			nbr = nbr * 10 + (*nstr - 48);
			nstr++;
			if ((nbr > 2147483647 && sign == 1) || (nbr > 2147483648))
				return (0);
		}
		if (*nstr != ' ' && *nstr != 0)
			return (0);
	}
	else
		return (0);
	return ((int)nbr * sign);
}

int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (is_space(str[i]))
		i++;
	if (*str == '-' || *str == '+')
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (is_space(str[i]))
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	ft_is_flag(char *str)
{
	if (str)
	{
		if (!str[0])
			return (0);
		if (str[0] && str[0] == '-')
		{
			str++;
			if (*str == 'n')
				while (*str == 'n')
					str++;
			else
				return (0);
		}
	}
	if (*str != 0)
		return (0);
	return (1);
}
