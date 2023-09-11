/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:35:39 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/11 08:48:32 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define WORD 0
# define R_DIR 1
# define L_DIR 2
# define RD_DIR 3
# define LD_DIR 4

typedef struct s_commande{
	char				*cmd;
	char				**cmds_split;
	int					id;
	char				*heredoc;
	struct s_commande	*next;
}	t_commande;

typedef struct s_partition
{
	t_commande			*cmds;
	struct s_partition	*next;
}	t_partition;

typedef struct s_vars
{
	t_list				*envp_list;
	char				**envp;
	t_partition			*parse_result;
}						t_vars;


#endif
