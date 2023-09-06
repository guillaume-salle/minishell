/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:42:35 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/05 20:37:25 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	afflistc(t_commande *var_env)
{
	while (var_env)
	{
		printf("%s\n", var_env->cmd);
		printf("%d\n", var_env->id);
		var_env = var_env->next;
	}
}

void	afflist(t_partition *var_env)
{
	while (var_env)
	{
		afflistc(var_env->cmds);
		var_env = var_env->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*commande;
	t_list		*var_env;
	char		**path;
	t_partition	*parse_result;

	(void)argc;
	(void)argv;
	var_env = initialized_env(env);
	path = ft_split(env[30], ':');
	while (1)
	{
		commande = readline("minishell> ");
		if (!ft_strcmp(commande, "oui")){
			rl_clear_history();
			break ;
		}
		add_history(commande);
		commande = first_transformation(commande, var_env);
		parse_result = parsing(commande);
		afflist(parse_result);
		if (commande)
			free(commande);
		free_parsing(&parse_result);
	}
	free(commande);
	ft_lstclear(&var_env, free);
	free_double_char(path);
	return (0);
}
// $?
// supp $$
// ""
