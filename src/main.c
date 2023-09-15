/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:43:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/15 22:48:28 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	g_sigint;

static void	afflistc(t_commande *var_env)
{
	if (var_env == NULL)
		printf("\tcommande nulle\n"); 
	while (var_env)
	{
		if (ft_strcmp(var_env->cmd, "") != 0)
			printf("\t\tCMD : %s\n", var_env->cmd);
		else
			printf("\t\tCMD : juste caractere nul\n");

		if (var_env->cmds_split == NULL)
			printf("\t\tCMDS_SPLIT : NULL");
		else
			printf("\t\tCMD_ARGS[0] : %s\n", var_env->cmds_split[0]);
		printf("\t\tID : %d\n", var_env->id);
		var_env = var_env->next;
	}
}

static void	afflist(t_partition *var_env)
{
	printf("--- PRINTING PARSING ---\n");
	if (var_env == NULL)
		printf("partition nulle\n");
	while (var_env)
	{
		afflistc(var_env->cmds);
		if (var_env->next)
			printf("\t|| next pipe || \n");
		var_env = var_env->next;
	}
	printf("--- END PARSING ---\n");
}

static void	reset_vars_zero(t_vars *vars)
{	
	free_partition(vars->parse_result);
	vars->parse_result = NULL;
	vars->last_pid = 0;
	vars->last_exit_status= 0;
	free(vars->line);
	vars->line = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars		vars;

	ft_memset(&vars, 0, sizeof(t_vars));
	setup_signal_handlers_main();
	init_envp_list(envp, &(vars.envp_list));
	while (1)
	{
		if (my_getenv("?", &vars) == NULL)
			my_putenv("?", "0", &vars);
		vars.line = readline("myshell> ");
		if (vars.line == NULL)
		{
			rl_clear_history();
			free_vars(&vars);
			exit(EXIT_SUCCESS);
		}
		if (!handle_history(vars.line))
		{
			free(vars.line);
			continue ;
		}
		vars.line = first_transformation(vars.line, &vars);
		vars.parse_result = parsing(vars.line);
		afflist(vars.parse_result);
		if (vars.parse_result != NULL)
			exec_partition_list(vars.parse_result, &vars);
		reset_vars_zero(&vars);
	}
	return ((void)argc, (void)argv, EXIT_SUCCESS);
}
