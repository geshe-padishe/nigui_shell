#include "minishell.h"

int	ft_exit(char **args, int nb_pipes)
{
	int i;

	if (nb_pipes)
		return (free(args - 1), -2);
	if (!args || !args[0])
		return (free(args - 1), 0);
	if (args[0] && args[1] && args[2])
		return (write(2, "exit: too many arguments\n", 25), free(args - 1), -2);
	if (!ft_is_number(args[0]))
		return (write(2, "exit: numeric argument required\n", 32), free(args - 1), -2);
	else
	{
		i = ft_ps_atoi(args[0]);
		return (free(args - 1), i);
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
	if (*str == '-' || *str == '+')
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	ft_is_flag(char *str)
{
	char *begin;

	begin = str;
	if (str)
	{
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
	if (*str != 0 && *str != ' ')
		return (0);
	return (str - begin);
}
