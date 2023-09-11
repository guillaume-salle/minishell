/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:43:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/11 09:16:47 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	g_sigint_received;

void	afflistc(t_commande *var_env)
{
	while (var_env)
	{
		printf("\t\tCMD : %s\n", var_env->cmd);
		printf("\t\tID : %d\n", var_env->id);
		var_env = var_env->next;
	}
}

void	afflist(t_partition *var_env)
{
	printf("--- PRINTING PARSING ---\n");
	while (var_env)
	{
		afflistc(var_env->cmds);
		if (var_env->next)
			printf("\t|| next pipe || \n");
		var_env = var_env->next;
	}
	printf("--- END PARSING ---\n");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars		vars;
	char		*line;

	ft_memset(&vars, 0, sizeof(t_vars));
	setup_signal_handlers_main();
	init_envp_list(envp, &(vars.envp_list));
	while (1)
	{
		line = readline("myshell> ");
		if (line == NULL)
		{
			rl_clear_history();
			free_vars(&vars);
			exit(EXIT_SUCCESS);
		}
		handle_history(line);
		line = first_transformation(line, vars.envp_list);
		vars.parse_result = parsing(line);
		afflist(vars.parse_result);
		exec_partition_list(vars.parse_result, &vars);
		free_partition(vars.parse_result);
		free(line);
	}
	return ((void)argc, (void)argv, EXIT_SUCCESS);
}
