/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:41:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/27 19:41:25 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "libft.h"
# include "get_next_line.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termios.h>

# define ECHO_OPTIONS "n"
# define OPTIONS_SIZE 128

extern volatile sig_atomic_t	g_signal_received;

// BUILTINS
int			echo(int argc, char *argv[], t_vars *vars);
int			env(int argc, char *argv[], t_vars *vars);
int			cd(int argc, char *argv[], t_vars *vars);
int			pwd(int argc, char *argv[], t_vars *vars);
int			export(int argc, char *argv[], t_vars *vars);
int			unset(int argc, char *argv[], t_vars *vars);
int			my_exit(int argc, char *argv[], t_vars *vars);

// UTILS
void		init_envp_list(char *envp[], t_list **head);
char		*my_getenv(const char *name, t_vars *vars);
int			my_putenv(const char *key, const char *value, t_vars *vars);
int			add_node(t_list **head, const char *name, const char *content);
bool		is_valid_variable_name(const char *name);
void		update_envp(t_vars *vars);
void		print_env(t_list *head);
void		print_env_export(t_list *head);
bool		check_spaces_append_history(char *line);
bool		is_builtin_command(t_commande *cmd_list);
void		increment_shlvl(t_vars *vars);

// PATH
char		*find_command_path(const char *command, t_vars *vars);
void		path_is_a_directory(char *pathname, t_vars *vars);
void		permission_denied(char *full_path, t_vars *vars);
char		*make_full_path(const char *path, const char *command,
				t_vars *vars);

// SIGNALS
//void		refresh_readline_sigint(void);
void		setup_signal_handlers_prompt(t_vars *vars);
void		setup_signal_handlers_heredoc(t_vars *vars);
void		setup_signal_handlers_default(t_vars *vars);
void		setup_signal_handlers_parent(t_vars *vars);
bool		signal_received(t_vars *vars);
bool		stop_signal_heredoc(t_vars *vars);
void		disable_ctrl_backslash(void);

// FREE
void		free_partition(t_partition *part);
void		free_list2(t_list *head);
void		free_vars(t_vars *vars);
void		display_error_and_exit(char *str, t_vars *vars);
void		free_and_nullify(char **pointer);
void		line_null_free_exit(t_vars *vars);

// EXECUTION
void		reset_vars_zero(t_vars *vars);
int			get_line_from_user(t_vars *vars);
void		exec_partition_list(t_partition *head, t_vars *vars);
bool		is_builtin(char *cmd_name);
int			handle_all_heredocs(t_partition *head, t_vars *vars);
void		exec_partition_with_pipe(t_partition *head, t_vars *vars);
int			exec_command_list(t_commande *head, t_vars *vars, bool forking);
int			handle_redirection(t_commande *cmd, t_vars *vars);
int			exec_word(t_commande *cmd, t_vars *vars, bool forking);
void		wait_for_children(t_vars *vars);

// SAFE
int			safe_dup(int oldfd, t_vars *vars);
int			safe_dup2(int oldfd, int newfd, t_vars *vars);
int			safe_close(int fd, t_vars *vars);
int			safe_pipe(int pipefd[2], t_vars *vars);

// PRINT PARSING
void		afflist(t_partition *var_env);

#endif
