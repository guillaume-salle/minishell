/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:41:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/15 22:46:09 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "libft.h"
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

# define ECHO_OPTIONS "n"
# define OPTIONS_SIZE 128

extern int	g_sigint;

// BUILTINS
int			echo(int argc, char *argv[], t_vars *vars);
int			env(int argc, char *argv[], t_vars *vars);
int			cd(int argc, char *argv[], t_vars *vars);
int			pwd(int argc, char *argv[], t_vars *vars);
int			export(int argc, char *argv[], t_vars *vars);
int			unset(int argc, char *argv[], t_vars *vars);

// UTILS
void		init_envp_list(char *envp[], t_list **head);
char		*my_getenv(const char *name, t_vars *vars);
int			my_putenv(const char *key, const char *value, t_vars *vars);
int			add_node(t_list **head, const char *name, const char *content);
bool		is_valid_variable_name(const char *name);
char		*find_command_path(const char *command, t_vars *vars);
void		update_envp(t_vars *vars);
void		print_env(const char *prefix, t_list *head);

// MAIN
void		setup_signal_handlers_main(void);
bool		handle_history(char *line);

// FREE
void		free_partition(t_partition *part);
void		free_list2(t_list *head);
void		free_vars(t_vars *vars);
void		display_error_and_exit(char *str, t_vars *vars);

// EXECUTION
void		exec_partition_list(t_partition *head, t_vars *vars);
bool		is_builtin(char *cmd_name);
void		handle_heredocs(t_partition *head, t_vars *vars);
int			exec_command_list(t_commande *head, t_vars *vars, bool forking);
void		handle_redirection(t_commande *cmd, t_vars *vars);
int			exec_word(t_commande *cmd, t_vars *vars, bool forking);

#endif
