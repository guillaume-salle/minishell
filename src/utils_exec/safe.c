/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:27:05 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 17:30:33 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

int	safe_dup(int oldfd, t_vars *vars)
{
	int	ret;

	ret = dup(oldfd);
	if (ret == -1)
		display_error_and_exit("dup", vars);
	return (ret);
}

int	safe_dup2(int oldfd, int newfd, t_vars *vars)
{
	int	ret;

	ret = dup2(oldfd, newfd);
	if (ret == -1)
		display_error_and_exit("dup2", vars);
	return (ret);
}

int	safe_close(int fd, t_vars *vars)
{
	int	ret;

	ret = close(fd);
	if (ret == -1)
		display_error_and_exit("close", vars);
	return (ret);
}

int	safe_pipe(int pipefd[2], t_vars *vars)
{
	int	ret;

	ret = pipe(pipefd);
	if (ret == -1)
		display_error_and_exit("pipe", vars);
	return (ret);
}
