/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 21:00:16 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/19 13:46:47 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

bool	check_spaces_append_history(char *line)
{
	if (!ft_str_isspace(line))
	{
		add_history(line);
		return (true);
	}
	else
		return (false);
}
