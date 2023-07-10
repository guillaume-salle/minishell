/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 16:22:53 by gusalle           #+#    #+#             */
/*   Updated: 2023/07/10 21:25:34 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **argv)
{
	char	*str;

	str = ft_strjoin_table(argv + 1, " ");
	if (str == NULL)
		return (1);
//	ft_putendl_fd(str, 1);
	ft_putstr_fd(*(argv+1), 1);
	ft_putstr_fd(" ", 1);
	ft_putendl_fd(*(argv+2), 1);
	free(str);
	return (0);
}

//#include <stdio.h>
//
//int	echo(char** strings) {
//    int i = 1;
//    while (strings[i] != NULL) {
//        printf("%s", strings[i]);
//        if (strings[i + 1] != NULL) {
//            printf(" ");
//        }
//        i++;
//    }
//    printf("\n");
//	return (0);
//}
//
