/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiccio <jmiccio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:04:08 by jmiccio           #+#    #+#             */
/*   Updated: 2024/09/12 13:03:48 by jmiccio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	print_format(va_list arg, const char format)
{
	void	*ptr;

	ptr = NULL;
	if (format == 'c')
		return (ft_putchar(va_arg(arg, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(arg, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(arg, int), 0));
	else if (format == 'X' || format == 'x')
		return (ft_puthexa(va_arg(arg, unsigned int), format));
	else if (format == 'p')
	{
		ptr = va_arg(arg, void *);
		if (ptr)
			return (ft_printaddress(ptr));
		else
			return (ft_putstr("(nil)"));
	}
	else if (format == 'u')
		return (ft_unsigned_putnbr(va_arg(arg, unsigned int), 0));
	else if (format == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;

	len = 0;
	if (!str)
		return (-1);
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && ft_strchr("cspdiuxX%", *(str + 1)))
		{
			len += print_format(args, *(str + 1));
			str++;
		}
		else
			len += ft_putchar(*str);
		str++;
	}
	va_end(args);
	return (len);
}

/*%c Imprime un seul caractère.
- %s Imprime une chaîne de caractères
(telle que définie par la convention C courante).
- %p L'argument du pointeur void * doit être imprimé au format hexadécimal.
- %d Imprime un nombre décimal (base 10).
- %i Imprime un nombre entier en base 10.
- %u Imprime un nombre décimal non signé (base 10).
- %x Imprime un nombre au format hexadécimal (base 16) en minuscules.
- %X Imprime un nombre au format hexadécimal (base 16) en majuscules.
- %% Imprime un signe de pourcentage.*/
