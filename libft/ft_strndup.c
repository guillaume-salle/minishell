/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:59:39 by gusalle           #+#    #+#             */
/*   Updated: 2023/08/11 17:03:36 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*cpy;
	size_t	len;

	len = ft_strnlen(s, n);
	cpy = malloc((len + 1) * sizeof(*cpy));
	if (cpy == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(cpy, s, len + 1);
	return (cpy);
}
