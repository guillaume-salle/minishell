/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:43:22 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/29 12:35:06 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_children(void)
{
	int		status;
	pid_t	pid;

	while ((pid = wait(&status)) > 0)
		;
	if (pid < 0 && errno != ECHILD)
	{
		perror("wait");
	}
}

void	exec_partition(t_partition *partitions, t_vars *vars)
{
	t_partition	*partition;
	t_commande	*command;
	int			pipe_fds[2];
	pid_t		pid;

	partition = partitions;
	while (partition != NULL)
	{
		int last_fd = -1; // For piping between commands
		command = partition->cmds;
		while (command != NULL)
		{
			if (command->next != NULL && pipe(pipe_fds) == -1)
			{
				perror("pipe");
				return ;
			}
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				return ;
			}
			if (pid == 0)
			{
				if (last_fd != -1)
				{
					dup2(last_fd, STDIN_FILENO);
					close(last_fd);
				}
				if (command->next != NULL)
				{
					dup2(pipe_fds[1], STDOUT_FILENO);
					close(pipe_fds[1]);
				}
				exec_single_command(command, vars);
				exit(EXIT_SUCCESS);
			}
			if (last_fd != -1)
				close(last_fd);
			if (command->next != NULL)
				close(pipe_fds[1]);
			last_fd = pipe_fds[0];
			command = command->next;
		}
		wait_for_children();
		partition = partition->next;
	}
}
