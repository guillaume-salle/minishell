/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:55:36 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/26 06:37:44 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

bool	is_valid_variable_name(const char *name)
{
	int	i;

	i = 0;
	if (name == NULL || *name == '\0')
	{
		return (false);
	}
	if (!ft_isalpha(name[i]) && name[i] != '_')
	{
		return (false);
	}
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

static void	free_exit_norm(char *key, char *value, t_vars *vars)
{
	if (key != NULL)
		free(key);
	if (value != NULL)
		free(value);
	display_error_and_exit("malloc", vars);
}

static void	print_error_message(char *key)
{
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static int	export_variable(const char *arg, t_vars *vars)
{
	char	*equals_sign;
	char	*key;
	char	*value;
	int		result;

	equals_sign = ft_strchr(arg, '=');
	if (equals_sign == NULL)
	{
		key = ft_strdup3(arg);
		value = NULL;
	}
	else
	{
		key = ft_strndup(arg, equals_sign - arg);
		value = ft_strdup3(equals_sign + 1);
	}
	if (key == NULL || (equals_sign != NULL && value == NULL))
		free_exit_norm(key, value, vars);
	if (!is_valid_variable_name(key))
		return (print_error_message(key), free(key), free(value), 1);
	result = my_putenv(key, value, vars);
	return (free(key), free(value), result);
}

// Returns 1 if at least one arg is invalid, else returns 0
// If no args, print env with prefix
int	export(int argc, char **argv, t_vars *vars)
{
	int	i;
	int	result;
	int	ret;

	if (argc == 1)
	{
		print_env_export(vars->envp_list);
		return (0);
	}
	ret = 0;
	i = 1;
	while (i < argc)
	{
		result = export_variable(argv[i], vars);
		if (result != 0)
			ret = result;
		i++;
	}
	return (ret);
}
