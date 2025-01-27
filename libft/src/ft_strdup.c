/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:16:59 by jmiccio           #+#    #+#             */
/*   Updated: 2024/09/10 17:18:06 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1, size_t size, int is_stash)
{
	char	*res;
	size_t	i;

	if (!s1)
		return (NULL);
	if (is_stash)
		res = (char *)malloc(sizeof(char) * size);
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
