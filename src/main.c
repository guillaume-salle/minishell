/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:43:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/16 19:31:19 by gusalle          ###   ########.fr       */
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
			printf("\t\tCMD : %s\n", var_env->cmd); else
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
	vars->exist_pipe = false;
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

//		int quote_open = 0;
//	    char quote_char = '\0';
//	    int pipe_open = 0;
//	
//	    while (1) {
//	        char *p = vars.line + ft_strlen(vars.line) - 1;
//	
//	        if (*p == '|') {
//	            pipe_open = 1;
//	        }
//	
//	        for (p = vars.line; *p; ++p) {
//	            if (*p == '\'' || *p == '\"') {
//	                if (quote_open && quote_char == *p) {
//	                    quote_open = 0;
//	                } else if (!quote_open) {
//	                    quote_open = 1;
//	                    quote_char = *p;
//	                }
//	            }
//	        }
//	
//	        if (!quote_open && !pipe_open) {
//	            break;
//	        }
//	
//	        char *next_line = readline("> ");
//	        if (next_line) {
//	            char *new_line = malloc(ft_strlen(vars.line) + ft_strlen(next_line) + 2);
//	            if (new_line) {
//	                strcpy(new_line, vars.line);
//	                strcat(new_line, "\n");
//	                strcat(new_line, next_line);
//	                free(vars.line);
//	                free(next_line);
//	                vars.line = new_line;
//	
//	                if (pipe_open && next_line[0] != '|') {
//	                    pipe_open = 0;
//	                }
//	
//	                for (p = next_line; *p; ++p) {
//	                    if (*p == quote_char) {
//	                        quote_open = !quote_open;
//	                    }
//	                }
//	            } else {
//					free(next_line);
//					display_error_and_exit("malloc", &vars);
//	            }
//	        } else { //EOF while expecting more
//				if (quote_open)
//					ft_putstr_fd("bash: unexpected EOF while looking for matching `''",
//							STDERR_FILENO);
//				ft_putstr_fd("minishell: syntax error: unexpected end of file",
//						STDERR_FILENO);
//				free(vars.line);
//				continue ; //??
//	        }
//	    }

		if (!handle_history(vars.line))
		{
			free(vars.line);
			continue ;
		}
		vars.line = first_transformation(vars.line, &vars);
		vars.parse_result = parsing(vars.line, &vars);
//		afflist(vars.parse_result);
		if (vars.parse_result != NULL)
			exec_partition_list(vars.parse_result, &vars);
		reset_vars_zero(&vars);
	}
	return ((void)argc, (void)argv, EXIT_SUCCESS);
}
