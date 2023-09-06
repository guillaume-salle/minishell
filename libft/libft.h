/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skhali <skhali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:59:58 by kyacini           #+#    #+#             */
/*   Updated: 2023/09/06 17:47:54 by gusalle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_list
{
	char			*content;
	char			*name;
	struct s_list	*next;
}					t_list;
int					ft_atoi(const char *nptr);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t elementCount, size_t elementSize);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
void				*ft_memchr(const void *memoryBlock, int searchedChar,
						size_t size);
int					ft_memcmp(const void *pointer1, const void *pointer2,
						size_t size);
void				*ft_memcpy(void *destination, const void *source,
						size_t size);
void				*ft_memmove(void *destination, const void *source,
						size_t size);
void				*ft_memset(void *pointer, int value, size_t count);
char				*ft_strchr(const char *string, int searchedChar);
char				*ft_strdup(char *src);
char				*ft_strjoin(char *s1, char *s2);
unsigned int		ft_strlcat(char *dest, const char *src, unsigned int size);
char				*ft_strtrim(char const *s1, char const *set);
unsigned int		ft_strlcpy(char *dest, const char *src, unsigned int size);
int					ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);
char				*ft_strnstr(const char *big, const char *little, int len);
char				*ft_strrchr(const char *string, int searchedChar);
char				*ft_substr(char *s, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				**ft_split(const char *str, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content, void *name);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strrejoin(int size, char **strs, char *sep, int start);
char				*ft_strcat(char *dest, char *src);

// ADD EXEC MINISHELL
char				*ft_strdup3(const char *src);
char				*ft_strjoin_table(char **argv, char *sep);
char				*ft_strndup(const char *s, size_t n);
size_t				ft_strnlen(const char *s, size_t n);
bool				ft_isspace(int c);
bool				ft_str_isspace(const char *str);
void				ft_free_split(char **tab);

#endif
