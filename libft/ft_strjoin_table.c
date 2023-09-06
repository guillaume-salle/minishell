/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:06:36 by gusalle           #+#    #+#             */
/*   Updated: 2023/07/17 11:41:48 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_total_length(char **argv, char *sep)
{
	size_t	len;
	char	**iter;

	iter = argv;
	len = 0;
	while (*iter)
	{
		len += ft_strlen(*iter);
		iter++;
		if (sep && *iter)
			len += ft_strlen(sep);
	}
	return (len);
}

char	*ft_strjoin_table(char **argv, char *sep)
{
	size_t	len;
	char	*str;
	char	**iter;

	if (!argv)
		return (NULL);
	len = get_total_length(argv, sep);
	str = calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	iter = argv;
	while (*iter)
	{
		ft_strlcat(str, *iter, len + 1);
		iter++;
		if (sep && *iter)
			ft_strlcat(str, sep, len + 1);
	}
	return (str);
}
