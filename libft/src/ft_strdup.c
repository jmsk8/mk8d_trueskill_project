/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:16:59 by jmiccio           #+#    #+#             */
/*   Updated: 2025/01/28 23:57:17 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char *dup;
	size_t len = strlen(s);

	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return NULL;

	for (size_t i = 0; i < len; i++)
		dup[i] = s[i];

	dup[len] = '\0';
	return dup;
}
