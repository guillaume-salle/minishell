/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:41:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/03 20:44:19 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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
# define WORD 0
# define R_DIR 1
# define L_DIR 2
# define RD_DIR 3
# define LD_DIR 4

extern int				g_sigint_received;

typedef struct s_list2
{
	char				*name;
	char				*content;
	struct s_list2		*next;
}						t_list2;

typedef struct s_vars
{
	t_list2				*envp_list;
	char				**envp;
}						t_vars;

typedef struct s_commande
{
	char				*cmd;
	char				**cmds_split;
	int					id;
	struct s_commande	*next;
}						t_commande;

typedef struct s_partition
{
	t_commande			*cmds;
	int					pid;
	struct s_partition	*next;
}						t_partition;

// BUILTINS
int						echo(int argc, char *argv[], t_vars *vars);
int						env(int argc, char *argv[], t_vars *vars);
int						cd(int argc, char *argv[], t_vars *vars);
int						pwd(int argc, char *argv[], t_vars *vars);
int						export(int argc, char *argv[], t_vars *vars);
int						unset(int argc, char *argv[], t_vars *vars);

// UTILS
void					init_envp_list(char *envp[], t_list2 **head);
char					*my_getenv(const char *name, t_vars *vars);
int						my_putenv(const char *key, const char *value,
							t_vars *vars);
int						add_node(t_list2 **head, const char *name,
							const char *content);
bool					is_valid_variable_name(const char *name);
char					*find_command_path(const char *command, t_vars *vars);
void					update_envp(t_vars *vars);

// MAIN
void					setup_signal_handlers_main(void);
void					handle_history(char *line);

// FREE
void					free_commande(t_commande *cmd);
void					free_partition(t_partition *part);
void					free_list2(t_list2 *head);
void					free_vars(t_vars *vars);

// TESTING
void					print_env(t_list2 *head);

// EXECUTION
void					exec_line(char *line, t_vars *vars);
int						exec_partition_list(t_partition *head, t_vars *vars);
void					pipe_and_fork(t_commande *cmd, t_vars *vars);
void					exec_command_list(t_commande *head, t_vars *vars);
void					exec_word(t_commande *cmd, t_vars *vars);
void					exec_r_rd(t_commande *cmd, t_vars *vars);
void					exec_l_dir(t_commande *cmd, t_vars *vars);
void					exec_ld_dir(t_commande *cmd, t_vars *vars);

#endif
