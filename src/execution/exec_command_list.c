/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:37:09 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/06 14:12:34 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command_list(t_commande *cmd_list, t_vars *vars) {
    t_commande *current = cmd_list;

    // Handle all redirections first
    while (current != NULL) {
        if (current->id != WORD) {
            handle_redirection(current);
        }
        current = current->next;
    }

    // Find and execute the WORD command
    current = cmd_list;
    while (current != NULL) {
        if (current->id == WORD) {
			exec_word(current, vars);
            break;
        }
        current = current->next;
    }
}
