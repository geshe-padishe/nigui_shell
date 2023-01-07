#include "minishell.h"

t_safe	g_vrac;

int	main(int ac, char **av, char **envp)
{
	t_dynarray	darr;
	int			ret;

	(void)av;
	if (ac != 1)
		return (-1);
	if (init_dyn_env(envp, &darr))
		return (-1);
	g_vrac.darr = &darr;
	signal(SIGINT, sigd_handler1);
	signal(SIGQUIT, sigd_handler2);
	ret = ft_readline(&darr);
	return (ft_readline(&darr), ft_free_all(&darr), dprintf(2, "MAIN ret = %d\n", ret), ret);
}
