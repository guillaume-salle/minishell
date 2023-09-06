/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:31:03 by kyacini           #+#    #+#             */
/*   Updated: 2022/05/11 19:55:09 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	debut(const char *chaine, const char *base)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (chaine[i])
	{
		while (base[j])
		{
			if (base[j] == chaine[i])
				break ;
			j++;
		}
		if (j == ft_strlen(base))
			break ;
		j = 0;
		i++;
	}
	return (i);
}

static void	norm(int bool, int *lum, int *memo, int *i)
{
	if (bool)
	{
		*lum = 0;
		*memo = 0;
	}
	*i += 1;
}

static void	ft_init(int *inter, int *i, int *j)
{
	*inter = 0;
	*i = 0;
	*j = 0;
}

static int	fin(const char *chaine, const char *base)
{
	int	inter;
	int	i;
	int	j;
	int	mem;

	ft_init(&inter, &i, &j);
	while (chaine[i])
	{
		while (base[j])
		{
			if (chaine[i] == base[j] && !inter)
			{
				mem = i;
				inter = 1;
				break ;
			}
			else if (chaine[i] == base[j] && inter)
				break ;
			j++;
		}
		norm(j == ft_strlen(base), &inter, &mem, &i);
		j = 0;
	}
	return (mem);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		supp_compte;
	char	*new_chaine;
	int		i;
	int		j;
	int		ca_end;

	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup(""));
	ca_end = fin(s1, set);
	if (!ca_end)
		ca_end = ft_strlen(s1);
	supp_compte = debut(s1, set) + (ft_strlen(s1) - ca_end);
	new_chaine = malloc(ft_strlen(s1) - supp_compte + 1);
	if (!new_chaine)
		return (NULL);
	new_chaine[ft_strlen(s1) - supp_compte] = '\0';
	i = 0;
	j = debut(s1, set);
	while (i < ft_strlen(s1) - supp_compte)
		new_chaine[i++] = s1[j++];
	return (new_chaine);
}
