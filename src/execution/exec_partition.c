/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_partition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:43:22 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/06 15:49:28 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static void	wait_for_children(void)
{
	int		status;
	pid_t	pid;

	pid = wait(&status);
	while (pid > 0)
		pid = wait(&status);
	if (pid < 0 && errno != ECHILD)
	{
		perror("wait");
	}
}

int	exec_partition_list(t_partition *head, t_vars *vars)
{
	t_commande	*command;
	int			pipe_fds[2];
	pid_t		pid;
	int			last_fd;

	//DELETE  CAST
	(void) vars;
	while (head!= NULL)
	{
		last_fd = -1;
		command = head->cmds;
		while (command != NULL)
		{
			if (command->next != NULL && pipe(pipe_fds) == -1)
			{
				perror("pipe");
				return (-1);
			}
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				return (-1);
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
				exec_command_list(command, vars);
				exit(EXIT_SUCCESS);
			}
			if (last_fd != -1)
				close(last_fd);
			if (command->next != NULL)
				close(pipe_fds[1]);
			last_fd = pipe_fds[0];
			command = command->next;
		}
		head = head->next;
	}
	wait_for_children();
	return (0);
}
