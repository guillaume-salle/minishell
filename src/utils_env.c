/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:15:26 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/11 13:01:12 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list2	*init_envp_list(char **envp)
{
	t_list2	*head;
	char	*key;
	char	*value;
	int		i;

	head = NULL;
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
		if (add_node(&head, key, value))
			return (NULL);
		envp++;
	}
	return (head);
}

int	add_node(t_list2 **head, const char *name, const char *content)
{
	t_list2	*new_node;

	new_node = malloc(sizeof(t_list2));
	if (new_node == NULL)
		return (-1);
	new_node->name = ft_strdup(name);
	if (new_node->name == NULL)
	{
		free(new_node);
		return (-1);
	}
	new_node->content = ft_strdup(content);
	if (new_node->content == NULL)
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
	t_list2	*current;

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
	t_list2	*current;

	if (key == NULL || value == NULL)
		return (-1);
	current = vars->envp_list;
	while (current)
	{
		if (ft_strcmp(current->name, key) == 0)
		{
			free(current->content);
			current->content = ft_strdup(value);
			if (!current->content)
				return (-1);
			return (0);
		}
		current = current->next;
	}
	if (add_node(&(vars->envp_list), key, value))
		return (-1);
	return (0);
}
