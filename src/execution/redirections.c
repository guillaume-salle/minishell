/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:02:34 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/11 09:27:02 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void handle_heredocs(t_partition *head, t_vars *vars) {
    t_partition *current_partition = head;
    t_commande *current_command;

    while (current_partition != NULL) {
        current_command = current_partition->cmds;
        while (current_command != NULL) {
            if (current_command->id == LD_DIR) {
                char *line;
                size_t total_length = 0;
                char *heredoc_data = NULL;

                // Read lines until the delimiter is found
                while (true) {
                    line = readline("> ");
                    if (line == NULL) {
                        display_error_and_exit("Failed to read heredoc data", vars);
                    }

                    // Check if the delimiter is reached
                    if (ft_strcmp(line, current_command->cmds_split[0]) == 0) {
                        free(line);
                        break;
                    }

                    // Calculate the new length and reallocate memory
                    size_t new_length = total_length + ft_strlen(line) + 1; // +1 for newline character
                    char *new_heredoc_data = realloc(heredoc_data, new_length + 1); // +1 for null terminator
                    if (new_heredoc_data == NULL) {
                        free(line);
                        free(heredoc_data);
                        display_error_and_exit("Memory allocation failed", vars);
                    }
                    heredoc_data = new_heredoc_data;

                    // Append the new data to the heredoc data
                    strcpy(heredoc_data + total_length, line); // Change strcpy
                    strcat(heredoc_data, "\n"); // Add newline character at the end. Change strcat
                    total_length = new_length;

                    free(line);
                }

                // Null terminate the heredoc data
                if (heredoc_data != NULL) {
                    heredoc_data[total_length] = '\0';
                }

                // Store the heredoc data in your data structure
                current_command->heredoc = heredoc_data;
            }
            current_command = current_command->next;
        }
        current_partition = current_partition->next;
    }
}

void handle_redirection(t_commande *cmd, t_vars *vars) {
    int fd;
	int pipefd[2];

    switch (cmd->id) {
        case R_DIR: // >
            fd = open(cmd->cmds_split[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
				display_error_and_exit("open", vars);
            if (dup2(fd, STDOUT_FILENO) == -1)
				display_error_and_exit("dup2", vars);
            close(fd);
            break;

        case L_DIR: // <
            fd = open(cmd->cmds_split[0], O_RDONLY);
            if (fd == -1)
				display_error_and_exit("open", vars);
            if (dup2(fd, STDIN_FILENO) == -1)
				display_error_and_exit("dup2", vars);
            close(fd);
            break;

        case RD_DIR: // >>
            fd = open(cmd->cmds_split[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
				display_error_and_exit("open", vars);
            if (dup2(fd, STDOUT_FILENO) == -1)
				display_error_and_exit("dup2", vars);
            close(fd);
            break;

		case LD_DIR: // <<
			if (pipe(pipefd) == -1)
				display_error_and_exit("pipe", vars);
			write(pipefd[1], cmd->heredoc, ft_strlen(cmd->heredoc));
			close(pipefd[1]);
			if (dup2(pipefd[0], STDIN_FILENO) == -1)
				display_error_and_exit("dup2", vars);
			close(pipefd[0]);
			break;

        default:
			display_error_and_exit("Invalid redirection type", vars);
    }
}
