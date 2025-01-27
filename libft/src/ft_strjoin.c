/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:41:40 by jmiccio           #+#    #+#             */
/*   Updated: 2024/09/10 12:56:13 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char *stash, char *buf)
{
	static size_t	size;
	char			*tmp;
	size_t			needed_size;

	tmp = NULL;
	if (!stash)
	{
		size = ft_strlen(buf) * 2;
		return (ft_strdup(buf, size, 1));
	}
	needed_size = ((ft_strlen(stash) + ft_strlen(buf)) + 1);
	if ((needed_size) >= size)
	{
		while (size <= (needed_size))
			size *= 2;
		tmp = ft_strdup(stash, size, 1);
		if (!tmp)
			return (free(stash), NULL);
		ft_strcat(tmp, buf);
		return (free(stash), tmp);
	}
	ft_strcat(stash, buf);
	return (stash);
}
