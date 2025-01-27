/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:32:50 by jmiccio           #+#    #+#             */
/*   Updated: 2024/09/15 18:09:38 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	get_num_of_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(long int n)
{
	char		*str;
	int			size;
	long int	num;
	int			sign;

	sign = 0;
	num = n;
	size = get_num_of_digits(num);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (NULL);
	if (num < 0)
	{
		num = -num;
		str[0] = '-';
		sign = 1;
	}
	str[size] = '\0';
	while (size > sign)
	{
		str[size - 1] = '0' + (num % 10);
		num /= 10;
		size--;
	}
	return (str);
}
