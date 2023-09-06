/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:02:34 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/06 14:17:43 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_redirection(t_commande *cmd) {
    int fd;

    switch (cmd->id) {
        case R_DIR: // >
            fd = open(cmd->cmds_split[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            break;

        case L_DIR: // <
            fd = open(cmd->cmds_split[1], O_RDONLY);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            break;

        case RD_DIR: // >>
            fd = open(cmd->cmds_split[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1) {
                perror("open");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            break;

        case LD_DIR: // <<
			{
				static int heredoc_count = 0;
				char *line = NULL;
				size_t len = 0;
				ssize_t read;
				char *delimiter = cmd->cmds_split[1];

				char heredoc_filename[20];
				sprintf(heredoc_filename, "heredoc_tmp%d", heredoc_count);
				heredoc_count++;

				fd = open(heredoc_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd == -1) {
					perror("open");
					exit(EXIT_FAILURE);
				}

				while ((read = getline(&line, &len, stdin)) != -1) {
					if (strcmp(line, delimiter) == 0) {
						break;
					}
					write(fd, line, read);
				}

				close(fd);
				free(line);

				fd = open(heredoc_filename, O_RDONLY);
				if (fd == -1) {
					perror("open");
					exit(EXIT_FAILURE);
				}
				dup2(fd, STDIN_FILENO);
				close(fd);

				// need to delete the temporary file once it is no longer needed
			}
			break;


        default:
            break;
    }
}
