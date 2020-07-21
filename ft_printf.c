/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 22:26:29 by lomeniga          #+#    #+#             */
/*   Updated: 2020/07/22 01:17:41 by lomeniga         ###   ########.fr       */
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
	*fmt = str - 1;
	return (nb);
}

int		parse_field(t_parse *parse)
{
	parse->width = ft_atoi(parse->fmt);
	return (0);
}

void	ft_putnbr(int n)
{
	int		nb;
	int		pow;
	int		neg;

	nb = n;
	pow = 1;
	neg = 1;
	while (nb /= 10)
		pow *= 10;
	if (n < 0)
		neg = -1;
	if (n < 0)
		write(1, "-", 1);
	while (pow)
	{
		write(1, &(char){(n / pow) * neg + '0'}, 1);
		n %= pow;
		pow /= 10;
	}
}

void	ft_putnbr_base_prec(int n, char base[], int len)
{
	int		nb;
	int		pow;
	int		neg;

	nb = n;
	pow = 1;
	neg = 1;
	while (nb /= len)
		pow *= len;
	if (n < 0)
		neg = -1;
	if (n < 0)
		write(1, "-", 1);
	while (pow)
	{
		write(1, base + ((n / pow) * neg), 1);
		n %= pow;
		pow /= len;
	}
}

void	pad_char(int n, char c)
{
	while (n > 0)
	{
		write(1, &c, 1);
		n--;
	}
}

int		number_len(int n, int base)
{
	unsigned len;

	len = 1;
	while (n /= base)
		len++;
	return (len);
}


int		conv_int(t_parse *parse)
{
	int		n;

	if (parse->prec >= 0)
		parse->pad = ' ';
	n = va_arg(*parse->ap, int);
	if (parse->prec < number_len(n, 10))
		parse->prec = number_len(n, 10);
	if (!parse->left)
		pad_char(parse->width - parse->prec, parse->pad);
	pad_char(parse->prec - number_len(n, 10), '0');
	ft_putnbr_base_prec(n, "0123456789", 10);
	if (parse->left)
		pad_char(parse->width - parse->prec, parse->pad);
	return (1);
}

int		conv_char()
{
	return (1);
}

int		conv_hex()
{
	return (1);
}

int		conv_pc()
{
	write(1, "%", 1);
	return (1);
}

int		conv_ptr()
{
	return (1);
}

int		conv_string()
{
	return (1);
}

int		conv_uns()
{
	return (1);
}

int		flag_aste(t_parse *parse)
{
	int		width;

	width = va_arg(*parse->ap, int);
	if (width < 0)
	{
		parse->width = - width;
		parse->left = 0;
	}
	else
		parse->width = width;
	return (0);
}

int		flag_min(t_parse *parse)
{
	parse->left = 1;
	return (0);
}

int		flag_prec(t_parse *parse)
{
	(*parse->fmt)++;
	if(**parse->fmt == '*')
	{
		(*parse->fmt)++;
		parse->prec = ft_atoi(parse->fmt);
	}
	else
		parse->prec = ft_atoi(parse->fmt);
	return (0);
}

int		flag_zero(t_parse *parse)
{
	if (!parse->left)
		parse->pad = '0';
	return (0);
}

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
	['u'] = conv_uns,
	['x'] = conv_hex,
	['X'] = conv_hex,
	['%'] = conv_pc,
	['-'] = flag_min,
	['0'] = flag_zero,
	['.'] = flag_prec,
	['*'] = flag_aste,
};

void	parse_format(char **fmt, va_list *ap)
{
	t_parse	parse;

	parse = (t_parse){.fmt = fmt, .ap = ap, .width = 0, .left = 0,
		.pad = ' ', .prec = -1};
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
	size_t		count;


	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
			parse_format((char **)&format, &ap);
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
