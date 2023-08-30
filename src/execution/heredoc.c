/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 17:23:40 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/30 11:45:46 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_ld_dir(t_commande *cmd, t_vars *vars)
{
	int		temp_fd;
	char	*line;
	int		fd;
	char	*delimiter;
	char	*temp_filename;

	delimiter = cmd->cmds_split[1];
	temp_filename = "/tmp/minishell_here_doc";
	temp_fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		perror("open");
		exit(1);
	}
	// Read input lines until delimiter is encountered
	line = NULL;
	while ((line = readline("> ")) != NULL) // Prompt symbol, can be customized
	{
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(temp_fd, line, ft_strlen(line));
		write(temp_fd, "\n", 1); // Add newline character
		free(line);
	}
	close(temp_fd);
	// Redirect standard input to temporary file
	fd = open(temp_filename, O_RDONLY);
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
