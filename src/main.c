/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:43:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/15 16:58:17 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_commande *command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(command->cmds_split[0], command->cmds_split) == -1)
		{
			perror("minishell");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("minishell");
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			waitpid(pid, &status, WUNTRACED);
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_vars	vars;

	argc++;
	(void) argv;
	vars.envp_list = init_envp_list(envp);
	if (!vars.envp_list)
		return (-1);
	return (0);
}
