/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:35:39 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/28 09:03:54 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define WORD 0
# define R_DIR 1
# define L_DIR 2
# define RD_DIR 3
# define LD_DIR 4

typedef struct s_commande
{
	char				*cmd;
	char				**cmds_split;
	int					id;
	char				*heredoc;
	char				*without_exp;
	struct s_commande	*next;
}						t_commande;

typedef struct s_partition
{
	t_commande			*cmds;
	struct s_partition	*next;
}						t_partition;

typedef struct s_vars
{
	t_list				*envp_list;
	char				**envp;
	char				*line;
	char				*old_line;
	char				*temp_line;
	t_partition			*parse_result;
	bool				forking;
	bool				exist_children;
	bool				exist_pipe;
	int					last_pid;
	int					last_exit_status;
	int					saved_stdin;
	int					saved_stdout;
	int					nb_line;
	bool				is_a_tty;
}						t_vars;

#endif
