/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:33:58 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/15 16:33:18 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "stdio.h"
# include "stdbool.h"
# include <sys/types.h>
# include <sys/wait.h>

# define ECHO_OPTIONS "n"
# define OPTIONS_SIZE 128

typedef struct s_list2
{
	char			*name;
	char			*content;
	struct s_list2	*next;
}	t_list2;

typedef struct s_vars
{
	t_list2	*envp_list;
}	t_vars;

typedef struct s_heredoc
{
	char	*filename;
	char	*file;
}	t_heredoc;

typedef struct s_commande{
	char				*cmd;
	int					argc;
	char				**cmds_split;
	int					id;
	t_heredoc			*hd;
	struct s_commande	*next;
}	t_commande;

int		echo(int argc, char *argv[], t_vars *vars);
int		env(int argc, char *argv[], t_vars *vars);
int		cd(int argc, char *argv[], t_vars *vars);
int		pwd(int argc, char **argv, t_vars *vars);
int		export(int argc, char **argv, t_vars *vars);
int		unset(int argc, char *argv[], t_vars *vars);

t_list2	*init_envp_list(char **envp);
char	*my_getenv(const char *name, t_vars *vars);
int		my_putenv(const char *key, const char *value, t_vars *vars);
int		add_node(t_list2 **head, const char *name, const char *content);
bool	is_valid_variable_name(const char *name);

//TESTING
void	execute_command(t_commande *command);
void	print_env(t_list2 *head);

#endif
