/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_from_user.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 08:57:54 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/21 10:51:42 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// skip the escape quote
//static bool	is_quote_open(char *line, char *quote_char)
//{
//	bool	is_quote_open;
//	char	current_quote_char;
//	int		i;
//
//	is_quote_open = false;
//	current_quote_char = '\0';
//	i = -1;
//	while (line[++i] != '\0')
//	{
//		if (line[i] == '\\' && (line[i + 1] == '\'' || line[i + 1] == '\"'))
//			i++;
//		else if (line[i] == '\'' || line[i] == '\"')
//		{
//			if (is_quote_open && current_quote_char == line[i])
//				is_quote_open = false;
//			else if (!is_quote_open)
//			{
//				is_quote_open = true;
//				current_quote_char = line[i];
//			}
//		}
//	}
//	if (is_quote_open && quote_char != NULL)
//		*quote_char = current_quote_char;
//	return (is_quote_open);
//}
//
//static bool	is_pipe_open(char *line)
//{
//	int	len;
//	int	i;
//
//	if (line == NULL)
//		return (false);
//	len = ft_strlen(line);
//	i = len - 1;
//	while (i >= 0)
//	{
//		if (ft_isspace(line[i]))
//			i--;
//		else if (line[i] == '|')
//			return (true);
//		else
//			return (false);
//	}
//	return (false);
//}
//
//static void	readline_null_expecting_more(t_vars *vars)
//{
//	char	quote_char;
//	char	*argv[2];
//
//	if (is_quote_open(vars->line, &quote_char))
//	{
//		ft_putstr_fd("minishell: unexpected EOF while looking for matching `",
//			STDERR_FILENO);
//		ft_putchar_fd(quote_char, STDERR_FILENO);
//		ft_putstr_fd("'\n", STDERR_FILENO);
//		my_putenv("?", "2", vars);
//		free(vars->line);
//		vars->line = NULL;
//	}
//	else if (is_pipe_open(vars->line))
//	{
//		ft_putstr_fd("minishell: syntax error: unexpected end of file\n",
//			STDERR_FILENO);
//		argv[0] = "exit";
//		argv[1] = "2";
//		my_exit(2, argv, vars);
//	}
//}
//
//static bool	get_line_from_user_2(t_vars *vars)
//{
//	while (is_pipe_open(vars->line) || is_quote_open(vars->line, NULL))
//	{
//		vars->old_line = vars->line;
//		vars->line = readline("> ");
//		if ((g_signal_received != 0) && signal_in_readline(vars) == true)
//		{
//			free(vars->old_line);
//			continue ;
//		}
//		if (vars->line == NULL)
//			return (readline_null_expecting_more(vars), false);
//		vars->temp_line = malloc(ft_strlen(vars->old_line)
//				+ ft_strlen(vars->line) + 2);
//		if (vars->temp_line == NULL)
//			display_error_and_exit("malloc", vars);
//		ft_strcpy(vars->temp_line, vars->old_line);
//		ft_strcat(vars->temp_line, "\n");
//		ft_strcat(vars->temp_line, vars->line);
//		free(vars->old_line);
//		free(vars->line);
//		vars->line = vars->temp_line;
//	}
//	return (true);
//}
//
//bool	get_line_from_user(t_vars *vars)
//{
//	if (vars->line == NULL)
//		vars->line = readline("minishell> ");
//	if (g_signal_received != 0)
//		signal_in_readline(vars);
//	if (vars->line == NULL)
//		readline_null_free_exit(vars);
//	if (get_line_from_user_2(vars) == false)
//		return (false);
//	return (true);
//}

int	get_line_from_user(t_vars *vars)
{
	setup_signal_handlers_prompt();
	if (vars->line == NULL && g_signal_received == 0)
		vars->line = readline("minishell> ");
	if (g_signal_received != 0)
		signal_in_readline(vars);
	if (vars->line == NULL)
		readline_null_free_exit(vars);
	if (!check_spaces_append_history(vars->line))
	{
		free_and_nullify(&vars->line);
		return (-1);
	}
	return (0);
}
