#include "minishell.h"

int	ft_cd(char **str)
{
	struct stat	stats;

	if (!*str)
		return (free(str - 1), 1);
	if (stat(*str, &stats))
		return (free(str - 1), perror("cd"), 1);
	if (!S_ISDIR(stats.st_mode))
		return (free(str - 1), perror("cd"), 1);
	else if (chdir(*str) == -1)
		return (free(str - 1), perror("cd"), 1);
	return (free(str - 1), 0);
}

int	ft_unset(t_dynarray *darr, char **str)
{
	int		index;
	char	**envp;
	int		i;

	i = 0;
	while (str && str[i])
	{
		envp = darr->list;
		index = ft_getenv_index(envp, darr->nb_cells, str[i], 0);
		if (index != -1)
		{
			free(envp[index]);
			dynarray_extract(darr, index, 1);
		}
		i++;
	}
	return (free(str - 1), 0);
}

int	ft_export(t_dynarray *darr, char **str)
{
	int		i_ind[2] = {0, 0};
	char	**envp;
	char	*envpi;

	while (str && str[i_ind[0]])
	{
		envp = darr->list;
		if (!ft_can_exp(str[i_ind[0]]))
			return (free(str - 1), 1);
		i_ind[1] = ft_getenv_index(envp, darr->nb_cells, str[i_ind[0]], 1);
		envpi = malloc(ft_strlen(str[i_ind[0]]) + 1);
		if (!envpi)
			return (free(str - 1), perror("malloc\n"), 1);
		ft_strcpy(str[i_ind[0]], envpi);
		if (i_ind[1] >= 0)
		{
			free(envp[i_ind[1]]);
			envp[i_ind[1]] = envpi;
		}
		else if (i_ind[1] == -1)
			if (push_dynarray(darr, &envpi, 1, 1))
				return (free(str - 1), perror("push_dynarray"), 1);
		i_ind[0]++;
	}
	return (free(str - 1), 0);
}

int	ft_pwd(char **args)
{
	char	pwd[1064];

	if (getcwd(pwd, 1064) == NULL)
		return (free(args - 1),
			perror("pwd: error retrieving current directory: getcwd: cannot access parent directories"), 1);
	return (printf("%s\n", pwd), free(args - 1), 0);
}

int	ft_echo(char **args)
{
	int		vars[4];

	ft_memset(vars, 0, 4 * sizeof(int));
	if (args && args[0])
	{
		while (args[vars[0]])
		{
			vars[3] = ft_is_flag(args[vars[0]]);
			if (vars[3] == 0)
				vars[2] = 1;
			else
				vars[1] = 1;
			if (vars[2])
			{
				printf("%s", args[vars[0]]);
				if (args[vars[0] + 1])
					printf(" ");
			}
			vars[0]++;
		}
	}
	if (!vars[1])
		printf("\n");
	return (free(args - 1), 1);
}
