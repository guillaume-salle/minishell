/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:43:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/18 19:15:32 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

volatile sig_atomic_t	g_signal_received = 0;

// To print parsing, uncomment and use this function :
// afflist(vars.parse_result);
int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	ft_memset(&vars, 0, sizeof(t_vars));
	setup_signal_handlers_main();
	init_envp_list(envp, &(vars.envp_list));
	while (1)
	{
		reset_vars_zero(&vars);
		if (my_getenv("?", &vars) == NULL)
			my_putenv("?", "0", &vars);
		get_line_from_user(&vars);
		if ((vars.line) == NULL)
			continue ;
		if (!handle_history(vars.line))
		{
			free(vars.line);
			continue ;
		}
		vars.line = first_transformation(vars.line, &vars);
		vars.parse_result = parsing(vars.line, &vars);
		if (vars.parse_result != NULL)
			exec_partition_list(vars.parse_result, &vars);
	}
	return ((void)argc, (void)argv, EXIT_SUCCESS);
}

//static void	afflistc(t_commande *var_env)
//{
//	if (var_env == NULL)
//		printf("\tcommande nulle\n");
//	while (var_env)
//	{
//		if (ft_strcmp(var_env->cmd, "") != 0)
//			printf("\t\tCMD : %s\n", var_env->cmd);
//		else
//			printf("\t\tCMD : juste caractere nul\n");
//		if (var_env->cmds_split == NULL)
//			printf("\t\tCMDS_SPLIT : NULL");
//		else
//			printf("\t\tCMD_ARGS[0] : %s\n", var_env->cmds_split[0]);
//		printf("\t\tID : %d\n", var_env->id);
//		var_env = var_env->next;
//	}
//}
//
//void	afflist(t_partition *var_env)
//{
//	printf("--- PRINTING PARSING ---\n");
//	if (var_env == NULL)
//		printf("partition nulle\n");
//	while (var_env)
//	{
//		afflistc(var_env->cmds);
//		if (var_env->next)
//			printf("\t|| next pipe || \n");
//		var_env = var_env->next;
//	}
//	printf("--- END PARSING ---\n");
//}
