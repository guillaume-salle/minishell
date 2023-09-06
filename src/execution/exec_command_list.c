/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:37:09 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/03 20:51:44 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	exec_command_list(t_commande *head, t_vars *vars)
{
	int		in_fd;
	int		out_fd;
	FILE	*tmp_fp;
	char	*line;
	size_t	len;
	ssize_t	read;

	(void)vars;
	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	tmp_fp = NULL;
	int here_doc_count = 0; // Counter for multiple here documents
	char tmp_file[50];      // To store the name of temporary files
	while (head != NULL)
	{
		switch (head->id)
		{
		case WORD:
			if (fork() == 0)
			{
				if (in_fd != STDIN_FILENO)
				{
					dup2(in_fd, STDIN_FILENO);
					close(in_fd);
				}
				if (out_fd != STDOUT_FILENO)
				{
					dup2(out_fd, STDOUT_FILENO);
					close(out_fd);
				}
				execvp(head->cmds_split[0], head->cmds_split);
				perror("execvp");
				exit(1);
			}
			else
			{
				wait(NULL);
				in_fd = STDIN_FILENO;
				out_fd = STDOUT_FILENO;
			}
			break ;
		case R_DIR:
			out_fd = open(head->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			break ;
		case RD_DIR:
			out_fd = open(head->cmd, O_WRONLY | O_CREAT | O_APPEND, 0644);
			break ;
		case L_DIR:
			in_fd = open(head->cmd, O_RDONLY);
			break ;
		case LD_DIR:
			here_doc_count++;
			sprintf(tmp_file, "tmp_here_doc_%d.txt", here_doc_count);
			tmp_fp = fopen(tmp_file, "w+");
			if (tmp_fp == NULL)
			{
				perror("fopen");
				exit(1);
			}
			line = NULL;
			len = 0;
			while ((read = getline(&line, &len, stdin)) != -1)
			{
				if (strncmp(line, head->cmd, strlen(head->cmd)) == 0)
				{
					break ;
				}
				fputs(line, tmp_fp);
			}
			free(line);
			fflush(tmp_fp);
			fseek(tmp_fp, 0, SEEK_SET);
			in_fd = fileno(tmp_fp);
			fclose(tmp_fp); // Close file after done writing
			tmp_fp = NULL;  // Reset the file pointer
			break ;
		default:
			break ;
		}
		head = head->next;
	}
	// Remove temporary files
	for (int i = 1; i <= here_doc_count; i++)
	{
		sprintf(tmp_file, "tmp_here_doc_%d.txt", i);
		remove(tmp_file);
	}
}
