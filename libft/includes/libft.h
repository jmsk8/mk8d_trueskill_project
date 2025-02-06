/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 02:12:39 by arthur            #+#    #+#             */
/*   Updated: 2025/02/05 23:00:28 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	**ft_split(char *s, char c);
int		ft_strcmp(char *str, char *cmp);
char	*ft_itoa(long int n);
void	ft_strcat(char *dst, const char *src);
int		ft_strlen(const char *s);
char	*ft_strncpy(char *str, int nb);
int		ft_charcpt(char *str, char chr);
char	*ft_strjoin(char *stash, char *buf);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);

/*ft_printf*/

int		ft_printf(const char *str, ...);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr(int n, int count);
int		ft_putaddress(unsigned long n);
int		ft_puthexa(unsigned int n, char format);
int		ft_printaddress(void *address);
int		ft_unsigned_putnbr(unsigned int n, int count);
char	*ft_strchr(char const *str, int c);
int		ft_strncmp(char const *s1, char const *s2, size_t n);

/*get_next_line*/

char	*get_next_line(int fd, int *is_error);
char	*ft_copy_to_stash(char *stash, char *buf, size_t *size);
void	*handle_error(char *stash, int *is_error, int rb, char *buf);
void	*manage_exit(char **stash, int create_line, int *is_error, int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup2(const char *s1, size_t size, int is_stash);

#endif
