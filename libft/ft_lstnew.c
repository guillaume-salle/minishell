/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyacini <kyacini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:11:43 by kyacini           #+#    #+#             */
/*   Updated: 2023/07/07 19:17:50 by kyacini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, void *name)
{
	t_list	*liste;

	liste = malloc(sizeof(t_list));
	if (!liste)
		return (NULL);
	liste->content = (void *)content;
	liste->name = name;
	liste->next = NULL;
	return (liste);
}
