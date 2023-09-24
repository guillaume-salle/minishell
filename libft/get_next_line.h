/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusalle <gusalle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 08:00:20 by gusalle           #+#    #+#             */
/*   Updated: 2022/03/09 08:00:22 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_gnl_buf
{
	ssize_t	ret;
	char	*content;
}				t_gnl_buf;

typedef struct s_gnl
{
	int			fd_max;
	t_gnl_buf	*tab;
}				t_gnl;

ssize_t	ft_realloc_tab(int n, t_gnl *gnl);
ssize_t	ft_realloc_line(char **linep, size_t *linecapp, ssize_t len);
int		ft_buf_in_line(char *linep, ssize_t *len, t_gnl_buf *buf, int delim);
void	ft_free_tab(int fd, t_gnl *gnl, ssize_t ret, ssize_t *len);
char	*get_next_line(int fd);

#endif
