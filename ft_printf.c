/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 22:26:29 by lomeniga          #+#    #+#             */
/*   Updated: 2020/07/31 14:48:38 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

int		(*(g_parse[256]))(t_parse *) = {
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
	['o'] = conv_octal,
	['u'] = conv_uns,
	['x'] = conv_hex,
	['X'] = conv_hex_up,
	['%'] = conv_pc,
	['-'] = flag_min,
	['0'] = flag_zero,
	['.'] = flag_prec,
	['*'] = flag_aste,
	[' '] = flag_space,
};

void	parse_format(char **fmt, va_list *ap, t_buf *buf)
{
	t_parse		parse;

	parse = (t_parse){ .fmt = fmt, .ap = ap, .prec = -1, .base = 10,
		.charset = "0123456789", .buf = buf, .pad = ' ' };
	(*fmt)++;
	while (g_parse[(unsigned)**fmt])
	{
		if (g_parse[(unsigned)**fmt](&parse))
			break ;
		(*fmt)++;
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_buf		buf;

	buf.total = 0;
	buf.index = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
			parse_format((char **)&format, &ap, &buf);
		else
			write_buf(&buf, *format);
		if (*format)
			format++;
	}
	va_end(ap);
	write(1, buf.buf, buf.index);
	return (buf.total);
}
