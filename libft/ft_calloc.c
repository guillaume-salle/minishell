/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:11:54 by kyacini           #+#    #+#             */
/*   Updated: 2022/05/11 18:36:16 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	char	*ptr;

	ptr = (char *)malloc(elementCount * elementSize * sizeof(char));
	if (!ptr || (elementCount > 65536 && elementSize > 65536))
		return (NULL);
	ft_bzero(ptr, elementCount * elementSize);
	return (ptr);
}
