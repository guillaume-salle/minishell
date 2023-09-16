/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:43:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 00:16:46 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"
#include "minishell_parsing.h"

int	g_sigint;

// static void	afflistc(t_commande *var_env)
// {
// 	if (var_env == NULL)
// 		printf("\tcommande nulle\n"); 
// 	while (var_env)
// 	{
// 		if (ft_strcmp(var_env->cmd, "") != 0)
// 			printf("\t\tCMD : %s\n", var_env->cmd); else
// 			printf("\t\tCMD : juste caractere nul\n");
// 
// 		if (var_env->cmds_split == NULL)
// 			printf("\t\tCMDS_SPLIT : NULL");
// 		else
// 			printf("\t\tCMD_ARGS[0] : %s\n", var_env->cmds_split[0]);
// 		printf("\t\tID : %d\n", var_env->id);
// 		var_env = var_env->next;
// 	}
// }
// 
// static void	afflist(t_partition *var_env)
// {
// 	printf("--- PRINTING PARSING ---\n");
// 	if (var_env == NULL)
// 		printf("partition nulle\n");
// 	while (var_env)
// 	{
// 		afflistc(var_env->cmds);
// 		if (var_env->next)
// 			printf("\t|| next pipe || \n");
// 		var_env = var_env->next;
// 	}
// 	printf("--- END PARSING ---\n");
// }

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

static void	readline_null_free_exit(t_vars *vars)
{
	rl_clear_history();
	free_vars(vars);
	exit(EXIT_SUCCESS);
}

// skip the escape quote
static bool	is_quote_open(char *line, char *quote_char)
{
    bool	is_quote_open;
    char	current_quote_char;
	int		i;
	
	is_quote_open = false;
	current_quote_char = '\0';
	i = -1;
	while (line[++i] != '\0')
	{
        if (line[i] == '\\' && (line[i + 1] == '\'' || line[i + 1] == '\"'))
            i++;
        else if (line[i] == '\'' || line[i] == '\"')
		{
            if (is_quote_open && current_quote_char == line[i])
                is_quote_open = false;
            else if (!is_quote_open)
			{
                is_quote_open = true;
                current_quote_char = line[i];
            }
        }
    }
    if (is_quote_open)
        *quote_char = current_quote_char;
    return is_quote_open;
}

static bool	is_pipe_open(char *line)
{
	int	len;
	int	i;

	if (line == NULL)
		return false;
    len = ft_strlen(line);
	i = len - 1;
	while (i >= 0)
	{
        if (ft_isspace(line[i]))
            i--;
        else if (line[i] == '|')
            return true;
        else
            return false;
    }
    return false;
}

//char *get_line_from_user(void)
//{
//	char *line = readline("myshell> ");
//    char *new_line = NULL;
//    char quote_char;
//    bool need_more_input = false;
//
//    do {
//        need_more_input = is_pipe_open(line) || is_quote_open(line, &quote_char);
//        if (need_more_input) {
//            new_line = readline("> ");
//            if (new_line) {
//                char *temp_line = malloc(strlen(line) + strlen(new_line) + 2);
//                if (temp_line) {
//                    strcpy(temp_line, line);
//                    strcat(temp_line, "\n");
//                    strcat(temp_line, new_line);
//                    free(line);
//                    free(new_line);
//                    line = temp_line;
//                } else {
//                    fprintf(stderr, "Memory allocation error\n");
//                    free(line);
//                    free(new_line);
//                    return NULL;
//                }
//            } else {
//                fprintf(stderr, "Error reading input\n");
//                free(line);
//                return NULL;
//            }
//        }
//    } while (need_more_input);
//
//    return line;
//}

void	get_line_from_user(t_vars *vars)
{
	char	quote_char;
	bool	need_more_input;

	vars->line = readline("minishell> ");
	if (vars->line == NULL)
		readline_null_free_exit(vars);
	need_more_input = is_pipe_open(vars->line) || is_quote_open(vars->line, &quote_char);
	while (need_more_input)
	{
		vars->new_line = readline("> ");
		if (vars->new_line == NULL)
			readline_null_free_exit(vars);
		vars->temp_line = malloc(ft_strlen(vars->line) + ft_strlen(vars->new_line) + 2);
		if (vars->temp_line == NULL)
			display_error_and_exit("malloc", vars);
		ft_strcpy(vars->temp_line, vars->line);
		ft_strcat(vars->temp_line, "\n");
		ft_strcat(vars->temp_line, vars->new_line);
		free(vars->line);
		free(vars->new_line);
		vars->line = vars->temp_line;
		need_more_input = is_pipe_open(vars->line) || is_quote_open(vars->line, &quote_char);
	}
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
		get_line_from_user(&vars);
//	        } else { //EOF while expecting more
//				if (quote_open && quote_char == '\'')
//					ft_putstr_fd("bash: unexpected EOF while looking for matching `''", STDERR_FILENO);
//				else if (quote_open && quote_char == '\"')
//					ft_putstr_fd("bash: unexpected EOF while looking for matching `\"'", STDERR_FILENO);
//				ft_putstr_fd("minishell: syntax error: unexpected end of file",
//						STDERR_FILENO);
//				free(vars.line);
//				continue ;
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
