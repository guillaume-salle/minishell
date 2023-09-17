/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:55:32 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 12:42:47 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

// Prints warning if EOF before delimiter is found
static void	end_of_file_heredoc(t_commande *current_command)
{
	ft_putstr_fd("minishell: warning: here-document at line ",
					STDERR_FILENO);
			ft_putnbr_fd(history_length, STDERR_FILENO);
			ft_putstr_fd(" delimited by end-of-file (wanted `",
					STDERR_FILENO);
			ft_putstr_fd(current_command->cmds_split[0], STDERR_FILENO);
			ft_putstr_fd("')\n", STDERR_FILENO);
}

// Read lines until the delimiter is found
static void	handle_this_heredoc(t_commande *current_command, t_vars *vars)
{
	char *line;
	size_t total_length = 0;
	char *heredoc_data = NULL;
	
	while (true) {
	    line = readline("> ");
	    if (line == NULL)
		{
			end_of_file_heredoc(current_command);
			break ;
		}
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

void	handle_all_heredocs(t_partition *head, t_vars *vars)
{
    t_partition *current_partition = head;
    t_commande *current_command;

    while (current_partition != NULL) {
        current_command = current_partition->cmds;
        while (current_command != NULL)
		{
            if (current_command->id == LD_DIR)
				handle_this_heredoc(current_command, vars);
            current_command = current_command->next;
        }
        current_partition = current_partition->next;
    }
}
