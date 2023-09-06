/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:26:25 by kyacini           #+#    #+#             */
/*   Updated: 2022/03/30 20:44:11 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_long_gen(int size, char **strs, char *sep, int start)
{
	int	i;
	int	count;
	i = start;
	count = 0;
	while (i < size)
	{
		count += ft_strlen(strs[i]);
		i++;
	}
	count += ft_strlen(sep) * (size - 1);
	return (count);
}

char	*ft_strrejoin(int size, char **strs, char *sep, int start)
{
	char	*res;
	int		i;

	if (start > size)
		start = 0;
	i = start;
	if (size == 0 )
	{
		res = malloc(sizeof(char));
		res[0] = '\0';
		return (res);
	}
	res = malloc(sizeof(char) * (ft_long_gen(size, strs, sep, start) + 1));
	if (!res)
		return (NULL);
	*res = '\0';
	while (i < size)
	{
		res = ft_strcat(res, strs[i]);
		i++;
		if (i < size)
			res = ft_strcat(res, sep);
	}
	return (res);
}