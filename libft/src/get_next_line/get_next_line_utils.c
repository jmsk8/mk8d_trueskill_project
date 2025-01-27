/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:52:28 by jmiccio           #+#    #+#             */
/*   Updated: 2024/09/26 15:45:46 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char *s1, size_t size, int is_stash)
{
	char	*res;
	size_t	i;

	if (!s1)
		return (NULL);
	if (is_stash)
		res = (char *)malloc(sizeof(char) * size + 1);
	else
		res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	ft_strcat(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0')
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	calc_len;

	calc_len = ft_strlen(s);
	if (!s || len <= 0)
		return (NULL);
	if (len > calc_len)
		len = calc_len;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = start;
	j = 0;
	while (i < calc_len && j < len)
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

void	*manage_exit(char **stash, int create_line, int *is_error, int n)
{
	char	*line;

	*is_error = n;
	if (!*stash)
		return (NULL);
	if (create_line == 0)
	{
		if (*stash)
		{
			free(*stash);
			*stash = NULL;
		}
		return (NULL);
	}
	line = ft_strdup(*stash, 0, 0);
	free(*stash);
	*stash = NULL;
	return (line);
}

void	*handle_error(char *stash, int *is_error, int rb, char *buf)
{
	free(buf);
	if ((rb == 0 && !stash))
		return (manage_exit(&stash, 0, is_error, 0));
	else
		return (manage_exit(&stash, 0, is_error, 1));
}
