/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:30:37 by kyacini           #+#    #+#             */
/*   Updated: 2022/05/11 19:56:52 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static void	ft_init(int *a, int *b, int *d)
{
	*a = 0;
	*b = 0;
	*d = 0;
}

char	*ft_strnstr(const char *big, const char *little, int len)
{
	int	i;
	int	j;
	int	c;

	if (!big || !little)
		return (NULL);
	ft_init(&i, &j, &c);
	if (len < 0)
		len = ft_strlen(big);
	while ((big[i] && i < len) || big[0] == '\0')
	{
		if (ft_strlen(little) > ft_strlen(big) - i)
			return (NULL);
		j = i;
		while (big[j] == little[c] && big[j] && little[c] && j < len)
		{
			c++;
			j++;
		}
		if (c == ft_strlen(little))
			return ((char *)big + i);
		i++;
		c = 0;
	}
	return (NULL);
}
