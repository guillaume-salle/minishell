/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:43:40 by kyacini           #+#    #+#             */
/*   Updated: 2022/05/11 19:58:14 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t size)
{
	size_t				i;
	const unsigned char	*new;
	const unsigned char	*renew;

	if (!pointer1 || !pointer2)
		return (0);
	new = pointer1;
	renew = pointer2;
	i = 0;
	while (i < size)
	{
		if (new[i] != renew[i])
			return (new[i] - renew[i]);
		i++;
	}
	return (0);
}
