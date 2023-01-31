/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nikishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngenadie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 23:46:47 by ngenadie          #+#    #+#             */
/*   Updated: 2023/01/31 16:45:28 by ngenadie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NIKISHELL_H

# include "dynarray.h"

# define PWD_ER "pwd: error retrieving current directory: "
# define CWD_ER "getcwd: cannot access parent directories: "
# define NO_FILE "No such file or directory"
# define ARGS "bash: exit: too many arguments\n"
# define ID ": not a valid identifier\n"

void	sig_pipehand(int i);
void	print_lst(t_lst *lst);
int		ft_rewind_fds(t_tout *tout);
int		ft_have_redirs(t_lst *lst);
void	prep_tout(t_tout *tout);
int		ft_is_built(t_lst *lst);
int		malloc_envpi(char **envpi, int i);
void	print_quoted(char *str);
char	*ft_strchr(char const *s, int c);
int		ft_print_env(t_dynarray *darr);
int		launch_child(t_tout *tout);
void	num_arg(char **args);
char	*ft_get_dir(char *path);
char	*ft_make_prompt(char *dir);
int		init_dyn_env(char **envp, t_dynarray *darr);
int		ft_dyn_env(t_dynarray *darr, char **str);
int		ft_getenv_index(char **envp, uint64_t len, char *str, bool un_exp);
int		ft_envcmp(char *str, char *str2);
bool	ft_can_exp(char *str);
int		ft_readline(t_dynarray *darr);
char	*ft_check_bin_path(char *bin, char *paths);
int		ft_find_bin(char *bin, char *paths, char **argv, char **envp);
int		ft_len_bef_col(char *paths);
void	sigd_handler1(int i);
void	sigd_handler2(int i);
void	siginthandler(int sig);
int		ft_pipes(t_lst *lst, t_tout *tout);
int		ft_wait_procs(int ac, pid_t *list);
int		ft_close_pipes(int **pipefd, int nb_pipes);
int		**create_pipe_arr(int nb_pipes);
void	free_pipe_array(int **pipefd, int nb_pipes);
int		ft_pipes_left(t_lst *lst);
char	*ft_strjoin(char *str, char *str2);
int		nk_strcmp(char const *str, char const *str2);
int		ft_check_env(t_dynarray *darr);
int		ft_open_create(char *filename, bool apnd_or_not, int token);
t_lst	*ft_next_pipe(t_lst *lst);
void	ft_print_pipes(int **pipefd, int nb_pipes);
void	ft_print_token(t_lst token);
void	ft_print_list(t_lst *token);
int		ft_handle_redirections(t_tout *tout, int alone);
int		ft_open_dup(t_lst *lst, int token, bool apnd_or_not);
int		ft_handle_exec(t_tout *tout);
int		ft_builtins_exec(t_lst *lst, t_dynarray *darr);
int		ft_pwd(char **args);
int		ft_echo(char **args);
int		ft_builtins(t_tout *tout);
void	ft_print_args(char **args);
void	ft_env(t_dynarray *darr);
int		ft_is_number(char *str);
int		ft_atoi_sign(char **nstr);
int		ft_ps_atoi(char *nstr);
char	**ft_splitargs(t_lst *lst);
int		ft_is_flag(char *str);
int		ft_exit(t_tout *tout, char **args);
int		ft_close_free(int **pipefd, int nb_pipes, t_lst *lst, t_dynarray *darr);
int		ft_export(t_dynarray *darr, char **str, char **envp);
int		ft_unset(t_dynarray *darr, char **str);
int		ft_cd(char **str);
t_lst	*find_bin_lst(t_lst *lst);
int		ft_is_dir(char *path_name);
void	ft_dir_error(char *path_name);
void	ft_perm_error(char *path_name);
void	ft_cmd_error(char *path_name);
void	ft_nofile_error(char *path_name);
void	ft_env_ptrs(t_dynarray *darr);
void	ft_free_env(t_dynarray *darr);
void	ft_free_all(t_dynarray *darr, t_lst *lst, int **pipefd, int nb_pipes);
void	ft_free_bcwrd(t_dynarray *darr, int i);

#endif
