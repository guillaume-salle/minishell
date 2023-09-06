/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:53:03 by kyacini           #+#    #+#             */
/*   Updated: 2023/08/31 14:27:58 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup2(char *src)
{
	char	*retour;
	int		i;
	int		taille;

	taille = 0;
	i = 0;
	if (!src)
		return (NULL);
	while (src[taille])
		taille++;
	retour = malloc(sizeof(char) * (taille + 1));
	if (!retour)
		return (NULL);
	while (src[i])
	{
		retour[i] = src[i];
		i++;
	}
	retour[i] = '\0';
	return (retour);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_chain;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup2(s2));
	new_chain = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_chain)
		return (NULL);
	new_chain[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	while (j < ft_strlen(s2) || (s2[0] == '\0' && j <= ft_strlen(s2)))
	{
		while (i < ft_strlen(s1))
		{
			new_chain[i] = s1[i];
			i++;
		}
		new_chain[i] = s2[j];
		i++;
		j++;
	}
	free(s1);
	return (new_chain);
}
