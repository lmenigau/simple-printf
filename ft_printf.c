/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 22:26:29 by lomeniga          #+#    #+#             */
/*   Updated: 2020/07/03 07:06:36 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

static int		ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static	int		is_space(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

int				ft_atoi(char **fmt)
{
	int		nb;
	int		neg;
	char	*str;

	str = *fmt;
	neg = 1;
	while (*str && is_space(*str))
		str++;
	nb = 0;
	if (*str == '-')
		neg = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str && ft_isdigit(*str))
	{
		nb = nb * 10 + (*str - '0') * neg;
		str++;
	}
	*fmt = str;
	return (nb);
}

int		parse_field(unsigned char **fmt, t_parse *parse)
{
	parse->width = ft_atoi((char **)fmt);
	return (0);
}

int		(*(g_parse[256]))(unsigned char **, t_parse *) = {
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

void	parse_format(unsigned char **fmt, va_list ap)
{
	t_parse	parse;

	va_copy(parse.ap, ap);
	(*fmt)++;
	while (g_parse[(int)**fmt])
	{
		if (g_parse[(int)**fmt](fmt, &parse))
			break ;
		(*fmt)++;
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	size_t		count;

	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
			parse_format((unsigned char **)&format, ap);
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
