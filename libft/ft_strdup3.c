/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:16:51 by gusalle           #+#    #+#             */
/*   Updated: 2023/09/16 18:22:07 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup3(const char *s)
{
	char	*cpy;

	if (s == NULL)
		return (NULL);
	cpy = malloc((ft_strlen(s) + 1) * sizeof(*cpy));
	if (cpy == NULL)
		return (NULL);
	ft_strlcpy(cpy, s, ft_strlen(s) + 1);
	return (cpy);
}
