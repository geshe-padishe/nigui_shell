#include "minishell.h"

t_safe			g_vrac;

int	main(int ac, char **av, char **envp)
{
	t_dynarray	darr;
	int			ret;

	av = NULL;
	ac = 0;
	if (init_dyn_env(envp, &darr))
		return (-1);
	g_vrac.status = 0;
	signal(SIGINT, siginthandler);
	signal(SIGQUIT, SIG_IGN);
	ret = ft_readline(&darr);
	return (ret);
}
