/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 22:26:29 by lomeniga          #+#    #+#             */
/*   Updated: 2020/07/03 05:07:55 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

int		(*(g_parse[256]))(unsigned char *, t_parse *) = {
	['1'] = parse_field,
	['2'] = parse_field,
	['3'] = parse_field,
	['4'] = parse_field,
	['5'] = parse_field,
	['6'] = parse_field,
	['7'] = parse_field,
	['8'] = parse_field,
	['9'] = parse_field,
	['c'] = conv_char,
	['s'] = conv_string,
	['p'] = conv_ptr,
	['d'] = conv_int,
	['i'] = conv_int,
	['u'] = conv_uns,
	['x'] = conv_hex,
	['X'] = conv_hex,
	['%'] = conv_pc,
	['-'] = flag_min,
	['0'] = flag_zero,
	['.'] = flag_prec,
	['*'] = flag_aste,
};

void	parse_format(unsigned char *fmt, va_list ap)
{
	t_parse	parse;

	va_copy(parse.ap, ap);
	while (g_parse[(int)*fmt])
	{
		g_parse[(int)*fmt](fmt, &parse);
		fmt++;
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	int			count;

	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
			parse_format((unsigned char *)format + 1, ap);
		else
		{
			write(1, format, 1);
			count++;
		}
		format++;
	}
	va_end(ap);
	return (count);
}

int		main(void)
{
	ft_printf("%c", 'c', 1.5f);
}
