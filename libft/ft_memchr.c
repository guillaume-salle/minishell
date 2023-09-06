/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:40:33 by kyacini           #+#    #+#             */
/*   Updated: 2022/05/11 19:59:07 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	size_t		i;
	const char	*new;

	i = 0;
	if (!memoryBlock)
		return (NULL);
	new = memoryBlock;
	while (i < size)
	{
		if (new[i] == (char)searchedChar)
			return ((void *)memoryBlock + i);
		i++;
	}
	return (NULL);
}
