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

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	is_space(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

int			ft_atoi(char **fmt)
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

int			parse_field(t_parse *parse)
{
	parse->width = ft_atoi(parse->fmt);
	return (0);
}

void		write_buf(t_buf *buf, char c)
{
		buf->buf[buf->index] = c;
		buf->index++;
		buf->total++;
		if (buf->index == 1024)
		{
			write(1, buf->buf, 1024);
			buf->index = 0;
		}
}

void		ft_putnbr_base_prec(t_buf *buf, unsigned long n, const char base[], int len)
{
	unsigned long	nb;
	unsigned long	pow;
	int				neg;

	nb = n;
	pow = 1;
	neg = 1;
	while (nb /= len)
		pow *= len;
	while (pow)
	{
		write_buf(buf, base[((n / pow) * neg)]);
		n %= pow;
		pow /= len;
	}
}

void		pad_char(t_buf *buf, int n, char c)
{
	while (n > 0)
	{
		write_buf(buf, c);
		n--;
	}
}

int			number_len(unsigned long n, int base)
{
	unsigned  len;

	len = 1;
	while (n /= base)
		len++;
	return (len);
}

void		print_unsigned(t_parse *parse)
{
	unsigned long  n;

	if (parse->prec >= 0)
		parse->zero = 0;
	n = va_arg(*parse->ap, unsigned int);
	if (parse->prec == 0 && n == 0)
		return ;
	if (parse->prec < parse->nlen)
		parse->prec = parse->nlen;
	pad_char(parse->buf, parse->prec - parse->nlen, '0');
	ft_putnbr_base_prec(parse->buf, n, parse->charset, parse->base);
}

void		print_signed(t_parse *parse)
{
	if (parse->neg)
		write_buf(parse->buf, '-');
	dprintf(9, "%d\n", parse->prec);
	pad_char(parse->buf, parse->pwidth - parse->nlen - (parse->zero && parse->neg), '0');
	if (parse->prec)
		ft_putnbr_base_prec(parse->buf, parse->nb, parse->charset, parse->base);
}

void		print_str(t_parse *parse)
{
	int  i;

	i = 0;
	while ((parse->prec > 0 && i < parse->prec && parse->str[i]) || (parse->prec < 0 &&  parse->str[i]))
	{
		write_buf(parse->buf, parse->str[i]);
		i++;
	}
}

size_t		ft_strlen(const char *s)
{
	size_t  len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void		print_field(t_parse *parse, void (f)(t_parse *))
{
	if (parse->left)
		f(parse);
	pad_char(parse->buf, parse->padlen, parse->pad);
	if (!parse->left)
		f(parse);
}

int			conv_int(t_parse *parse)
{

	if (parse->prec >= 0)
	{
		parse->zero = 0;
		parse->pad = ' ';
	}
	if (parse->zero)
		parse->prec = parse->width;
	parse->nb = va_arg(*parse->ap, int);
	parse->neg = (parse->nb < 0);
	if (parse->neg)
		parse->nb = -parse->nb;
	parse->nlen = number_len(parse->nb, parse->base);
	if (!parse->prec && !parse->nb)
		parse->nlen = 0;
	parse->pwidth = parse->nlen;
	if (parse->prec > parse->nlen)
		parse->pwidth = parse->prec;
	parse->padlen = parse->width - parse->pwidth - parse->neg;
	print_field(parse, print_signed);
	return (1);
}

void		print_char(t_parse *parse)
{
	unsigned char  c;

	c = va_arg(*parse->ap, int);
	write_buf(parse->buf, c);
}

int			conv_char(t_parse *parse)
{
	parse->padlen = parse->width - 1;
	print_field(parse, print_char);
	return (1);
}

int			conv_hex(t_parse *parse)
{
	if (parse->prec >= 0)
		parse->padlen = parse->width - parse->prec;
	parse->base = 16;
	parse->charset = "0123456789abcdef";
	print_field(parse, print_unsigned);
	return (1);
}

int			conv_hex_up(t_parse *parse)
{
	if (parse->prec >= 0)
		parse->padlen = parse->width - parse->prec;
	parse->base = 16;
	parse->charset = "0123456789ABCDEF";
	print_field(parse, print_unsigned);
	return (1);
}

int			conv_pc()
{
	write(1, "%", 1);
	return (1);
}

int			conv_ptr(t_parse *parse)
{
	if (parse->prec >= 0)
		parse->padlen = parse->width - parse->prec;
	parse->base = 16;
	parse->charset = "0123456789abcdef";
	print_field(parse, print_unsigned);
	return (1);
}

int			conv_string(t_parse *parse)
{
	parse->str = va_arg(*parse->ap, char *);
	int len = ft_strlen(parse->str);
	parse->padlen = parse->width;
	if (parse->prec >= 0 && parse->prec < len)
		len = parse->prec;
	parse->padlen -= len;
	print_field(parse, print_str);
	return (1);
}

int			conv_uns(t_parse *parse)
{
	print_field(parse, print_unsigned);
	return (1);
}

int			flag_aste(t_parse *parse)
{
	int  width;

	width = va_arg(*parse->ap, int);
	if (width < 0)
	{
		parse->width = -width;
		parse->left = 0;
	}
	else
		parse->width = width;
	return (0);
}

int			flag_min(t_parse *parse)
{
	parse->left = 1;
	return (0);
}

int			flag_prec(t_parse *parse)
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

int			flag_zero(t_parse *parse)
{
		parse->zero = 1;
		parse->pad = '0';
	return (0);
}

int     (*(g_parse[256]))(t_parse *) = {
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
	['X'] = conv_hex_up,
	['%'] = conv_pc,
	['-'] = flag_min,
	['0'] = flag_zero,
	['.'] = flag_prec,
	['*'] = flag_aste,
};

void		parse_format(char **fmt, va_list *ap, t_buf *buf)
{
	t_parse   parse;

	parse = (t_parse){ .fmt = fmt, .ap = ap, .width = 0, .left = 0, .zero = 0,
		.prec = -1, .base = 10, .charset = "0123456789", .buf = buf, .pad = ' ' };
	(*fmt)++;
	while (g_parse[(unsigned)**fmt])
	{
		if (g_parse[(unsigned)**fmt](&parse))
			break;
		(*fmt)++;
	}
}

int			ft_printf(const char *format, ...)
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
		{
			write_buf(&buf, *format);
			buf.total++;
		}
		format++;
	}
	va_end(ap);
	write(1, buf.buf, buf.index);
	return (buf.total);
}
