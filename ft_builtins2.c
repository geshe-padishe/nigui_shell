#include "minishell.h"

int	ft_exit(char **args, int nb_pipes)
{
	if (nb_pipes)
		return (-2);
	if (!args || !args[0])
		return (0);
	if (args[0] && args[1] && args[2])
		return (write(2, "exit: too many arguments\n", 25), -2);
	if (!ft_is_number(args[0]))
		return (write(2, "exit: numeric argument required\n", 32), -2);
	else
		return (ft_ps_atoi(args[0]));
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