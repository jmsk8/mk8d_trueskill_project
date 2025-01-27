/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:50:55 by jmiccio           #+#    #+#             */
/*   Updated: 2024/09/12 13:03:52 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_putaddress(unsigned long n)
{
	char			*base;
	int				count;
	unsigned int	base_len;

	base = "0123456789abcdef";
	count = 0;
	base_len = 16;
	if (n >= base_len)
		count += ft_putaddress(n / base_len);
	count += ft_putchar(base[n % base_len]);
	return (count);
}

int	ft_puthexa(unsigned int n, char format)
{
	char			*base;
	int				count;
	unsigned int	base_len;

	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	count = 0;
	base_len = 16;
	if (n >= base_len)
		count += ft_puthexa(n / base_len, format);
	count += ft_putchar(base[n % base_len]);
	return (count);
}

int	ft_printaddress(void *address)
{
	unsigned long	n;
	int				len;

	n = (unsigned long)address;
	len = ft_putstr("0x");
	len += ft_putaddress(n);
	return (len);
}
