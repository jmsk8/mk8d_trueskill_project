/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:02:01 by jmiccio           #+#    #+#             */
/*   Updated: 2024/09/12 13:03:45 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strchr(char const *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	else
		return (NULL);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
		i += ft_putchar(str[i]);
	return (i);
}

int	ft_putnbr(int n, int count)
{
	long	num;

	num = n;
	if (num < 0)
	{
		num = -num;
		count += ft_putchar('-');
	}
	if (num >= 10)
	{
		count = ft_putnbr(num / 10, count);
	}
	count += ft_putchar((num % 10) + '0');
	return (count);
}

int	ft_unsigned_putnbr(unsigned int n, int count)
{
	if (n >= 10)
	{
		count = ft_unsigned_putnbr(n / 10, count);
	}
	count += ft_putchar((n % 10) + '0');
	return (count);
}
