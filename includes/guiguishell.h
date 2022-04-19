#ifndef GUIGUISHELL_H

# include "nikishell.h"

typedef struct s_token
{
	int			is_redirection_input;
	int			is_redirection_output;
	int			is_here_doc;
	int			is_append_output;
	int			is_word;
	int			is_wrong;
	int			nb_word;
	char		*elem;
}	t_token;

typedef struct s_split
{
	char	**split;
	int		i;
	int		j;
	char	quote;
	int		single_quote;
	int		double_quote;
	int		nb_split;
}	t_split;

typedef struct s_indexer
{
	int		*begin_word;
	int		*end_word;
	int		nb_word;
	char	quote;
}	t_index;

/*
 *	ft_token.c
 */

t_token	*ft_token(t_split *split);

/*
 *	string_utils.c
 */

void	count_double_quotes(char *str, t_split *split);
void	count_simple_quotes(char *str, t_split *split);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
int		skip_space(char *str);

/*
 *	ft_quote.c
 */

void	to_quote_or_not_to_quote(char *str, int i, t_split *split);
void	index_to_quote_or_not_to_quote(char *str, int i, t_index *index);
int		is_quoted_good(char *str);

/*
 *	parser.c
 */

int	parse(char *line_buffer);

/*
 *	redo_split.c
 */

void	tab_init(int *tab, int len);
int		redo_split(char *str, t_split *split);

/*
 *	indexer.c
 */

t_index	*init_indexer(char *str);
t_index	*indexing(char *str, t_split *split);

/*
 *	ft_is.c
 */

int		is_meta_char(t_token *token, int i);
void	which_is(t_token *token, int i);

/*
 *	unload.c
 */

void	unload(t_split *split, t_token *token);
void	unload_indexer(t_index *index);

/*
 *	seek_meta_char.c
 */

int		which_meta_char(t_token *token, int i_tok, int i_str);
int		seek_meta_char(t_token *token, int i);
int		seek_and_count_meta_char(t_token *token, int i);

/*
 *	decompose_indexer.c
 */

t_index *decompose_indexer(t_token *token, int target);

/*
 *	decompose_token.c
 */

t_token	*decompose_token(t_token *old_token, int target);

#endif