/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:43:16 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/17 17:43:18 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

static void	exit_init(t_list **head)
{
	free_list2(*head);
	perror("init_envp");
	exit(EXIT_FAILURE);
}

void	init_envp_list(char *envp[], t_list **head)
{
	char	*key;
	char	*value;
	int		i;

	while (*envp)
	{
		i = 0;
		while ((*envp)[i] != '\0')
		{
			if ((*envp)[i] == '=')
			{
				(*envp)[i] = '\0';
				key = *envp;
				value = *envp + i + 1;
				break ;
			}
			i++;
		}
		if (add_node(head, key, value))
			exit_init(head);
		(*envp)[i] = '=';
		envp++;
	}
}

int	add_node(t_list **head, const char *name, const char *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (-1);
	new_node->name = ft_strdup3(name);
	if (new_node->name == NULL)
	{
		free(new_node);
		return (-1);
	}
	new_node->content = ft_strdup3(content);
	if (content != NULL && new_node->content == NULL)
	{
		free(new_node->name);
		free(new_node);
		return (-1);
	}
	new_node->next = *head;
	*head = new_node;
	return (0);
}

char	*my_getenv(const char *name, t_vars *vars)
{
	t_list	*current;

	current = vars->envp_list;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

int	my_putenv(const char *key, const char *value, t_vars *vars)
{
	t_list	*current;

	if (key == NULL)
		return (-1);
	current = vars->envp_list;
	while (current)
	{
		if (ft_strcmp(current->name, key) == 0)
		{
			free(current->content);
			current->content = ft_strdup3(value);
			if (value != NULL && current->content == NULL)
				return (-1);
			return (0);
		}
		current = current->next;
	}
	if (add_node(&(vars->envp_list), key, value))
		return (-1);
	return (0);
}
