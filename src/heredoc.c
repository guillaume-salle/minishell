/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:23:40 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/23 17:24:23 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_ld_dir(t_commande *cmd, t_vars *vars)
{
    char *delimiter = cmd->cmds_split[1]; // Get the delimiter
    char *temp_filename = "/tmp/minishell_here_doc"; // Temporary file
    int temp_fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (temp_fd == -1)
    {
        perror("open");
        exit(1);
    }

    // Read input lines until delimiter is encountered
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, stdin) != -1)
    {
        if (strcmp(line, delimiter) == 0)
            break;
        write(temp_fd, line, strlen(line));
    }
    free(line);
    close(temp_fd);

    // Redirect standard input to temporary file
    int fd = open(temp_filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        exit(1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        exit(1);
    }
    close(fd);

    // Execute the command with redirected input
    my_execvp(cmd->cmds_split, vars);

    // Delete the temporary file
    unlink(temp_filename);
}
