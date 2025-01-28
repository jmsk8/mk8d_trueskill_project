/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:44:53 by jmiccio           #+#    #+#             */
/*   Updated: 2025/01/28 23:59:08 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_copy_to_stash(char *stash, char *buf, size_t *size)
{
	char		*tmp;
	size_t		needed_size;

	tmp = NULL;
	if (!stash)
		return (ft_strdup2(buf, *size, 1));
	needed_size = ((ft_strlen(stash) + ft_strlen(buf)) + 1);
	if ((needed_size * 2) >= *size)
	{
		while (*size <= (needed_size * 2))
			*size *= 2;
		tmp = ft_strdup2(stash, *size, 1);
		if (!tmp)
			return (free(stash), NULL);
		ft_strcat(tmp, buf);
		return (free(stash), tmp);
	}
	ft_strcat(stash, buf);
	return (stash);
}

static int	ft_have_nl(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_extract_line(char *stash)
{
	size_t	i;
	size_t	copy_size;
	char	*line;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		copy_size = i + 1;
	else
		copy_size = i ;
	line = ft_substr(stash, 0, copy_size);
	return (line);
}

static char	*ft_extract_and_recreat_stash(char **stash, int *is_error)
{
	size_t	i;
	char	*res;
	char	*line;

	i = 0;
	if (!*stash)
		return (NULL);
	line = ft_extract_line(*stash);
	if (!line)
		return (manage_exit(stash, 0, is_error, 1));
	while ((*stash)[i] != '\n' && (*stash)[i] != '\0')
		i++;
	if ((*stash)[i + 1] == '\0')
		return (manage_exit(stash, 0, is_error, 0), line);
	res = ft_substr(*stash, i + 1, ft_strlen(*stash) - i - 1);
	if (!res)
		return (free(line), manage_exit(stash, 0, is_error, 1));
	free(*stash);
	*stash = res;
	return (line);
}

char	*get_next_line(int fd, int *is_error)
{
	char		*buf;
	long		rb;
	static char	*stash = NULL;
	size_t		current_size;

	current_size = (BUFFER_SIZE * 2);
	rb = BUFFER_SIZE;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (manage_exit(&stash, 0, is_error, 1));
	while (1)
	{
		rb = read(fd, buf, BUFFER_SIZE);
		if ((rb == 0 && !stash) || rb == -1)
			return (handle_error(stash, is_error, rb, buf));
		buf[rb] = '\0';
		stash = ft_copy_to_stash(stash, buf, &current_size);
		if (!stash)
			return (free(buf), manage_exit(&stash, 0, is_error, 1));
		if (ft_have_nl(stash))
			return (free(buf), ft_extract_and_recreat_stash(&stash, is_error));
	}
	return (NULL);
}
