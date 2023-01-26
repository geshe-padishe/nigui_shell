#ifndef COMMON_H
# define COMMON_H

# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/types.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <stdint.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_dynarray
{
	void		*list;
	void		*tmp;
	size_t		cell_size;
	uint64_t	nb_cells;
	uint64_t	byte_size;
}				t_dynarray;

typedef struct s_lst
{
	char			*str;
	int				token;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;
//	lst->str = "ls -la fsdljgod"
//	lst->token = 0 string
//				= 1 pipe
//				= 2 >
//				= 3 <
//				= 4 >>
//				= 5 <<
typedef struct s_safe
{
	int			status;
}	t_safe;

typedef struct s_tout
{
	t_lst		*lst;
	t_dynarray	*darr;
	int			**pipefd;
	int			nb_pipes;
	int			i;
	int			pipes_left;
	int			fd_in;
	int			ret_built;
	int			ret_wait;
	int			b_or_w;
	pid_t		*list;
}	t_tout;

extern t_safe	g_vrac;

char	*ft_getenvval(char *str, t_dynarray *darr,
			bool val_or_all, bool un_or_exp);
void	*ft_memset(void *s, int c, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
