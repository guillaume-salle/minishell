/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 23:02:34 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/10 22:27:01 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void handle_redirection(t_commande *cmd, t_vars *vars) {
    int fd;

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
            fd = open(cmd->cmds_split[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
				display_error_and_exit("open", vars);
            if (dup2(fd, STDOUT_FILENO) == -1)
				display_error_and_exit("dup2", vars);
            close(fd);
            break;

//		case LD_DIR: // <<
//			fd = open(cmd->hd->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
//            if (fd == -1)
//				display_error_and_exit("open", vars);
//            if (dup2(fd, STDOUT_FILENO) == -1)
//				display_error_and_exit("dup2", vars);
//            close(fd);
//			break;

        default:
			display_error_and_exit("Invalid redirection type", vars);
    }
}
