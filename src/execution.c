/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:37:09 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/16 19:11:27 by gusalle          ###   ########.fr       */
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

void exec_command(t_commande *cmd) {
    if (cmd->id == WORD) {
        if (execvp(cmd->cmds_split[0], cmd->cmds_split) == -1) {
            perror("minishell: command not found");
            exit(EXIT_FAILURE);
        }
    }
    // Further redirection cases and other id types can be handled here
    // E.g., R_DIR, L_DIR, etc.
}

void exec_partition(t_partition *part) {
    int pipe_fd[2];
    int pid;

    for (t_commande *cmd = part->cmds; cmd != NULL; cmd = cmd->next) {
        if (cmd->next) {  // If there's a next command, set up a pipe
            if (pipe(pipe_fd) == -1) {
                perror("minishell: pipe error");
                exit(EXIT_FAILURE);
            }
        }

        pid = fork();

        if (pid == 0) {  // Child
            if (cmd->next) {
                close(pipe_fd[0]);  // Close read end
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }

            exec_command(cmd);
            exit(EXIT_SUCCESS);
        } else if (pid > 0) {  // Parent
            wait(NULL);  // Wait for child to finish

            if (cmd->next) {
                close(pipe_fd[1]);  // Close write end
                dup2(pipe_fd[0], STDIN_FILENO);
                close(pipe_fd[0]);
            }
        } else {
            perror("minishell: fork error");
            exit(EXIT_FAILURE);
        }
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
