/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:34:38 by jmiccio           #+#    #+#             */
/*   Updated: 2024/09/15 17:07:05 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_charcpt(char *str, char chr)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (!(str))
		return (0);
	while (str[i])
	{
		if (str[i] == chr)
			ret++;
		i++;
	}
	return (ret);
}

static size_t	ft_strlen_split(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	*write_str(char const *s, char **array, size_t num_of_split, char c)
{
	size_t	i;
	size_t	str_size;

	i = 0;
	while (i < num_of_split)
	{
		while (*s == c)
			s++;
		str_size = ft_strlen_split(s, c) + 1;
		array[i] = (char *)malloc(sizeof(char) * str_size);
		if ((!array[i]))
		{
			while (i > 0 && --i)
				free(array[i]);
			free(array[i]);
			free(array);
			return (NULL);
		}
		ft_strlcpy(array[i], s, str_size);
		s += str_size;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char *s, char c)
{
	char	**array;
	size_t	num_of_split;

	if (!s)
		return (NULL);
	num_of_split = ft_charcpt(s, c);
	array = (char **)malloc(sizeof(char *) * (num_of_split + 1));
	if (!array)
		return (free(s), NULL);
	if (write_str(s, array, num_of_split, c) == NULL)
		return (free(s), NULL);
	free(s);
	return (array);
}
