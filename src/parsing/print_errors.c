/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:55:51 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/17 19:33:36 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	print_err_token(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
}

void	print_err_newline(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
}

void	print_err_pipe(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
}

void	print_err_single(void)
{
	ft_putstr_fd("Error with a single quote\n", STDERR_FILENO);
}
