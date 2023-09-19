/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:57:02 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/19 20:52:09 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int	d;
	int	i;

	d = ft_strlen(dest);
	i = 0;
	while (src[i])
	{
		dest[d] = src[i];
		i++;
		d++;
	}
	dest[d] = '\0';
	return (dest);
}
