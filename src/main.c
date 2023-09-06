/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:43:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/06 17:55:41 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	g_sigint_received;

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
		printf("||| next pipe\n");
		var_env = var_env->next;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars		vars;
	char		*line;
	t_partition	*parse_result;

	(void)argc;
	(void)argv;
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
		parse_result = parsing(line);
		afflist(parse_result);
		//		exec_line(line, &vars);
		free(line);
	}
	return (EXIT_SUCCESS);
}
