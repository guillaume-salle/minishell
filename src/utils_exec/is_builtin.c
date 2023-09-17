/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:40:47 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 17:41:18 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

bool	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (false);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (true);
	return (false);
}
