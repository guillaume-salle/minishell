/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 07:58:47 by gusalle           #+#    #+#             */
/*   Updated: 2022/03/09 07:58:49 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	ft_alloc_buf(int fd, t_gnl *gnl, ssize_t ret)
{
	if (ret < 0)
		return (-1);
	if ((gnl->tab)[fd].content == NULL)
	{
		(gnl->tab)[fd].content = malloc(BUFFER_SIZE * sizeof(char));
		if ((gnl->tab)[fd].content == NULL)
			return (-1);
		(gnl->tab)[fd].ret = 0;
	}
	return (1);
}

static ssize_t	ft_getdelim(char **linep, size_t *linecapp, int delimiter,
		int fd)
{
	static t_gnl	gnl;
	ssize_t			ret;
	ssize_t			len;

	len = 0;
	ret = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (-1);
	if (gnl.tab == NULL || gnl.fd_max < fd)
		ret = ft_realloc_tab(fd, &gnl);
	ret = ft_alloc_buf(fd, &gnl, ret);
	while (0 < ret)
	{
		ret = ft_realloc_line(linep, linecapp, len);
		if (ret < 0 || ft_buf_in_line(*linep, &len, gnl.tab + fd, delimiter))
			break ;
		ret = read(fd, (gnl.tab)[fd].content, BUFFER_SIZE);
		(gnl.tab)[fd].ret = ret;
	}
	ft_free_tab(fd, &gnl, ret, &len);
	return (len);
}

static ssize_t	ft_getline(char **linep, size_t *linecapp, const int fd)
{
	return (ft_getdelim(linep, linecapp, '\n', fd));
}

char	*get_next_line(int fd)
{
	char	*linep;
	size_t	linecapp;
	ssize_t	n;

	linep = NULL;
	linecapp = 0;
	n = ft_getline(&linep, &linecapp, fd);
	if (n == -1)
		return (NULL);
	if (n == 0)
	{
		free(linep);
		return (NULL);
	}
	return (linep);
}
