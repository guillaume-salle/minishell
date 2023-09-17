/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:48:47 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/17 14:08:06 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "structs.h"

t_list			*initialized_env(char **env);
void			free_double_char(char	**str);
t_partition		*ft_lstnew_partition(char *cmd, t_vars *var_env);
void			ft_lstadd_back_partition(t_partition **lst, t_partition *new);
t_partition		*ft_lstlast_partition(t_partition *lst);
t_partition		*create_partition(char **partitions, t_vars *var_env);
t_partition		*parsing(char *line, t_vars *var_env);
t_commande		*create_lstcmd(char *str, t_vars *var_env);
t_commande		*ft_lst_newcmd(char *without_exp, char *cmd, int id);
void			ft_lstadd_backcmd(t_commande **lst, t_commande *new);
t_commande		*ft_lstlastcmd(t_commande *lst);
char			*create_word(char **str, int *tab, t_vars *var_env);
int				*create_type_table(char **div, int *tab);
int				check_unique(char *str);
char			*first_transformation(char *commande, t_vars *var_env);
int				*create_quote_rep(char *str);
char			*add_spaces(char *str);
char			*supp_quotes(char *str, t_vars *var_env, int id);
void			clean_del(char **str);
char			**stock_variables(char *str);
char			*illuminate_variables(char *str, t_list *var_env, char **vars);
void			free_parsing(t_partition **partition);
char			*join_char(char *s1, char c);
int				count_char(char **vars, t_list *var_env);
void			variable(char *str, int *i, char **new);
void			case_tab(int *tab, int *i, int type);
void			fill_tab(char *str, int *quotes, char *new);
void			init_var_addspace(int *i, int *c, int *tab);
void			new_tab_with_spaces(int **tab, int *c);
char			*add_final(char *str, int *tab, int size, int *quotes);
int				*create_add_space(int *tab, int position, int size);
void			fill_quote_tab(int *cases, int *switch_ab, int a, int b);
int				*init_var_createquote(int *a, int *b, int *i, char *str);
void			fill_lstcmd(char **div, int *tab, t_commande **c, t_vars *var_env);
void			init_vars_count(int *i, int *res, int *len_var);
void			add_var_len(char *var, t_list *var_env, int *res);
void			init_var_illum(int *i, int *c, int *j);
void			affect_casu_char(char *new, char str, int *j);
int				check_red(char *str);

#endif
