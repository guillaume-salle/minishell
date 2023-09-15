/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:55:36 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/15 13:31:19 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

bool	is_valid_variable_name(const char *name)
{
	int i;

	i = 0;
	if (!name || !*name)
	{
		return (printf("minishell: export: `%s': not a valid identifier\n", name), false);
	}
	if (!ft_isalpha(name[i]) && name[i] != '_')
	{
		return (printf("minishell: export: `%s': not a valid identifier\n", name), false);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			return (printf("minishell: export: `%s': not a valid identifier\n", name), false);
		}
		i++;
	}
	return (true);
}

static int	import_variable(const char *arg, t_vars *vars)
{
	char	*equals_sign;
	char	*key;
	char	*value;
	int		result;

	equals_sign = ft_strchr(arg, '='); // free ?
	key = ft_strndup(arg, equals_sign - arg);
	if (!is_valid_variable_name(key) || !equals_sign || equals_sign == arg)
		return (free(key), 0);
	value = ft_strdup3(equals_sign + 1);
	if (!key || !value)
	{
		ft_putstr_fd("Memory allocation failed\n", STDERR_FILENO);
		free(key);
		free(value);
		return (-1);
	}
	if (!is_valid_variable_name(key))
		return (free(key), free(value), 0);
	result = my_putenv(key, value, vars);
	free(key);
	free(value);
	return (result);
}

int	export(int argc, char **argv, t_vars *vars)
{
	int	i;
	int	result;

	if (argc < 2)
	{
		ft_putstr_fd("Usage: export KEY1=VALUE1 KEY2=VALUE2 ...\n",
			STDERR_FILENO);
		return (-1);
	}
	i = 1;
	while (i < argc)
	{
		result = import_variable(argv[i], vars);
		if (result != 0)
			return (result);
		i++;
	}
	return (0);
}
