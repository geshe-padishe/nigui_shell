/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniparsing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 00:55:55 by hkhater           #+#    #+#             */
/*   Updated: 2023/01/31 19:46:45 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIPARSING_H
# define MINIPARSING_H

# include "dynarray.h"

# define SYNTAX_ERR "bash: syntax error near unexpected token `"

// Parsing.c
t_lst	*parse(char *line, int ext, t_dynarray *darr);

// Quotes.c
int		var_name_len(char *str);
char	*protect_content(char *str, int rev);
char	*dup_quote(char *s);

// Heredoc.c + hd_utils.c
char	*find_limiter(char *s);
char	*namefile(void);
void	here_sig(int sig);
void	ft_child_sig(int sig);
char	*has_heredoc(char *line);
int		act_has_quote(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*mult_heredoc(char *line, int ext, t_dynarray *darr);
void	neg_quotes(char *s);

// Syntax.c
int		syntax_check(char *line);

// is.c
int		ft_isdigit(int c);
int		is_alnumund(int c);
int		is_redir(char c);
int		is_operator(char c);
int		is_sep(char c);

// Expand.c
int		find_dollar(char *str);
char	*trio_merge(char *before, char *value, char *after);
char	*my_expand(char *str, int ext, t_dynarray *darr);

// Libft.c + Libft_utils.c
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_itoa(int n);
size_t	unquote_len(const char *str);
char	*ft_free(char *str1, char *str2, char *str3, char *str4);
void	safe_free(char *line, char *str);

// is_token.c
int		is_space(char c);
int		is_quote(char c);
int		has_quote(char *str);
int		recognize_op(char *str);

// Tokenization
t_lst	*tokenize(char *line);

// Lst.c
t_lst	*first_lst(t_lst *lst);
void	free_lst(t_lst *src);
void	push_lst(t_lst *neww, t_lst *lst);
char	*put_err(char *str);
int		lst_len(t_lst *lst);
t_lst	*new_lst(void);
void	push_first_lst(t_lst *neww, t_lst *lst);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strcp(char *s, unsigned int start, size_t len);

int		init_my_expand(int *i_len, char **expanded, int ext, char **exit);
int		init_parse(char **exp, char **hd, int *upd);
int		open_heredoc_file(int *fd, char *file, char **limiter, int *qu);
int		manage_expand_in_heredoc(char **line, int ext, t_dynarray *darr);
int		write_user_input(int fd, char *line);

#endif
