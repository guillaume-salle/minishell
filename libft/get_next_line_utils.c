/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 07:59:33 by gusalle           #+#    #+#             */
/*   Updated: 2022/03/09 07:59:35 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	ft_realloc_tab(int fd, t_gnl *gnl)
{
	t_gnl_buf	*temp;
	int			i;

	temp = gnl->tab;
	gnl->tab = malloc((2 * fd + 1) * sizeof(*gnl->tab));
	if (gnl->tab == NULL)
		return (-1);
	i = 0;
	while (i <= 2 * fd)
	{
		(gnl->tab)[i].content = NULL;
		if (i <= gnl->fd_max && (temp != NULL && temp[i].content != NULL))
		{
			(gnl->tab)[i].content = temp[i].content;
			(gnl->tab)[i].ret = temp[i].ret;
		}
		i++;
	}
	gnl->fd_max = 2 * fd;
	if (temp != NULL)
		free(temp);
	return (1);
}

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (src == NULL && dest == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)(dest))[i] = ((char *)(src))[i];
		i++;
	}
	return (dest);
}

ssize_t	ft_realloc_line(char **linep, size_t *linecapp, ssize_t len)
{
	char	*temp;

	if (((len + BUFFER_SIZE + 1) - (BUFFER_SIZE) - 1) != len)
		return (-1);
	if ((size_t)(len + BUFFER_SIZE + 1) < *linecapp)
		return (1);
	if (((2 * len + BUFFER_SIZE + 1) - len) != len + BUFFER_SIZE + 1)
		return (-1);
	temp = *linep;
	*linep = malloc((2 * len + BUFFER_SIZE + 1) * sizeof(**linep));
	if (*linep == NULL)
	{
		*linep = temp;
		return (-1);
	}
	*linecapp = 2 * len + BUFFER_SIZE + 1;
	if (temp != NULL)
	{
		ft_memcpy(*linep, temp, len);
		free (temp);
	}
	(*linep)[len] = 0;
	return (1);
}

int	ft_buf_in_line(char *linep, ssize_t *len, t_gnl_buf *buf, int delimiter)
{
	ssize_t	i;

	i = 0;
	while (i < buf->ret && !(0 < i && (buf->content)[i - 1] == delimiter))
		i++;
	ft_memcpy(linep + *len, buf->content, i);
	ft_memcpy(buf->content, buf->content + i, buf->ret - i);
	*len += i;
	linep[*len] = 0;
	buf->ret -= i;
	if (0 < *len && linep[*len - 1] == delimiter)
		return (1);
	else
		return (0);
}

void	ft_free_tab(int fd, t_gnl *gnl, ssize_t ret, ssize_t *len)
{
	int	i;

	if (ret <= 0)
	{
		free((gnl->tab)[fd].content);
		(gnl->tab)[fd].content = NULL;
		i = 0;
		while (i <= gnl->fd_max && (gnl->tab)[i].content == NULL)
			i++;
		if (i == gnl->fd_max + 1)
		{
			free(gnl->tab);
			gnl->tab = NULL;
		}
	}
	if (ret < 0)
		*len = -1;
}
