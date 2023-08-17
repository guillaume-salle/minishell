/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:37:09 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/17 19:15:37 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void exec_command(t_commande *cmd) {
//    int fd;
//
//    if (!cmd) return;
//
//    switch (cmd->id) {
//        case R_DIR:
//            fd = open(cmd->cmds_split[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//            if (fd == -1) {
//                perror("open"); exit(1);
//            }
//            dup2(fd, STDOUT_FILENO);
//            close(fd);
//            execvp(cmd->cmds_split[0], cmd->cmds_split);
//            perror("execvp");
//            exit(1);
//            break;
//        case L_DIR:
//            fd = open(cmd->cmds_split[1], O_RDONLY);
//            if (fd == -1) {
//                perror("open");
//                exit(1);
//            }
//            dup2(fd, STDIN_FILENO);
//            close(fd);
//            execvp(cmd->cmds_split[0], cmd->cmds_split);
//            perror("execvp");
//            exit(1);
//            break;
//        case RD_DIR:
//            fd = open(cmd->cmds_split[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
//            if (fd == -1) {
//                perror("open");
//                exit(1);
//            }
//            dup2(fd, STDOUT_FILENO);
//            close(fd);
//            execvp(cmd->cmds_split[0], cmd->cmds_split);
//            perror("execvp");
//            exit(1);
//            break;
//        case LD_DIR:
//            // Handle heredoc '<<'
//            break;
//        case WORD:
//            execvp(cmd->cmd, cmd->cmds_split);
//            perror("execvp");
//            exit(1);
//            break;
//    }
//}

void	child_routine(int pipe_fd[2], t_commande *cmd, t_vars *vars)
{
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	exec_command(cmd, vars);
	exit(EXIT_SUCCESS);
}

void	parent_routine(int pipe_fd[2], t_commande *cmd)
{
	wait(NULL);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
}

void	pipe_and_fork(t_commande *cmd, t_vars *vars)
{
    int			pipe_fd[2];
    int			pid;

	if (cmd->next)
	{
		if (pipe(pipe_fd) == -1) {
			perror("minishell: pipe error");
			exit(EXIT_FAILURE);
		}
	}
	pid = fork();
	if (pid == 0)
	{
		child_routine(pipe_fd, cmd, vars);
	}
	else if (pid > 0)
	{
		parent_routine(pipe_fd, cmd);
	}
	else
	{
	    perror("minishell: fork error");
	    exit(EXIT_FAILURE);
	}
}

void exec_partition(t_partition *part, t_vars *vars)
{
	t_commande	*cmd;

	cmd = part->cmds;
	while (cmd != NULL)
	{
		pipe_and_fork(cmd, vars);
		cmd = cmd->next;
    }
}

//int main() {
//    t_partition *part = // ... Initialize your partitions
//
//    while (part) {
//        exec_partition(part);
//        part = part->next;
//    }
//
//    return 0;
//}
