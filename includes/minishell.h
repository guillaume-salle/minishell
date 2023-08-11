/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:33:58 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/11 12:42:03 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "stdio.h"

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

void	echo(int argc, char **argv);
void	env(t_list2 *head);
int		cd(int argc, char *argv[], t_vars *vars);

t_list2	*init_envp_list(char **envp);
char	*my_getenv(const char *name, t_vars *vars);
int		my_putenv(const char *key, const char *value, t_vars *vars);
int		add_node(t_list2 **head, const char *name, const char *content);

#endif
