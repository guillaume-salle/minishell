/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:15:43 by kyacini           #+#    #+#             */
/*   Updated: 2022/05/11 19:57:56 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t size)
{
	unsigned char		*new;
	const unsigned char	*renew;

	if (!destination && !source)
		return (NULL);
	new = destination;
	renew = source;
	if (new > renew)
	{
		while (size--)
			new[size] = renew[size];
	}
	else
		(ft_memcpy(destination, source, size));
	return (destination);
}
