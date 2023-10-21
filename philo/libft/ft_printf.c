/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:43:28 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/10 14:48:36 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_hex_up(unsigned int n, unsigned int *ct)
{
	if (n > 15)
	{
		ft_putnbr_hex_up(n / 16, ct);
	}
	write(1, &("0123456789ABCDEF"[n % 16]), 1);
	(*ct)++;
}

void	ft_putnbr_hex_low(unsigned int n, unsigned int *ct)
{
	if (n > 15)
	{
		ft_putnbr_hex_low(n / 16, ct);
	}
	write(1, &("0123456789abcdef"[n % 16]), 1);
	(*ct)++;
}

void	print_handle(const char *format, va_list args, unsigned int i, \
unsigned int *ct)
{
	if (format[i] == 'c')
		ft_putchar(va_arg(args, int), ct);
	else if (format[i] == 's')
		ft_putstr(va_arg(args, char *), ct);
	else if (format[i] == 'p')
	{
		write(1, "0x", 2);
		*ct += 2;
		ft_putptr(va_arg(args, void *), ct);
	}
	else if (format[i] == 'd' || format[i] == 'i')
		ft_putnbr(va_arg(args, int), ct);
	else if (format[i] == 'u')
		ft_putnbr_u(va_arg(args, unsigned), ct);
	else if (format[i] == 'x')
		ft_putnbr_hex_low(va_arg(args, unsigned), ct);
	else if (format[i] == 'X')
		ft_putnbr_hex_up(va_arg(args, unsigned), ct);
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	unsigned int	i;
	unsigned int	ct;

	va_start(args, format);
	i = 0;
	ct = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '%')
				ft_putchar(format[i], &ct);
			else
				print_handle(format, args, i, &ct);
		}
		else
			ft_putchar(format[i], &ct);
		i++;
	}
	va_end(args);
	return (ct);
}
