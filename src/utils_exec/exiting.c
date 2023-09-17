/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 09:47:09 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 09:47:35 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	display_error_and_exit(char *str, t_vars *vars)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(str);
	free_vars(vars);
	exit(errno);
}
