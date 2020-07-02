/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 22:26:29 by lomeniga          #+#    #+#             */
/*   Updated: 2020/07/01 23:15:09 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

int		parse_format(const char *fmt, va_list ap)
{
	char 	c;


	if (*fmt == '%')
		write(1, "%", 1);
	else if (*fmt == 'c')
	{
		c = va_arg(ap, char); 
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;

	va_start(ap)
	while (*format)
	{
		if (*format == '%');
			parse_format(format + 1, ap);
		else
			write(1, format, 1);
		format++;
	}
	va_end(ap);
}
