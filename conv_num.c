/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 12:30:28 by lomeniga          #+#    #+#             */
/*   Updated: 2020/09/14 12:30:30 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		conv_uns(t_parse *parse)
{
	parse->nb = va_arg(*parse->ap, unsigned int);
	conv_num(parse);
	print_field(parse, print_unsigned);
	return (1);
}

int		conv_int(t_parse *parse)
{
	parse->nb = va_arg(*parse->ap, int);
	parse->neg = (parse->nb < 0);
	if (parse->neg)
		parse->nb = -parse->nb;
	conv_num(parse);
	if (!parse->neg)
		parse->padlen -= parse->space;
	if (parse->zero && !parse->neg && parse->space)
		write_buf(parse->buf, ' ');
	print_field(parse, print_signed);
	return (1);
}

int		conv_hex(t_parse *parse)
{
	parse->nb = va_arg(*parse->ap, unsigned int);
	parse->base = 16;
	parse->charset = "0123456789abcdef";
	conv_num(parse);
	print_field(parse, print_unsigned);
	return (1);
}

int		conv_octal(t_parse *parse)
{
	parse->nb = va_arg(*parse->ap, unsigned int);
	parse->base = 8;
	parse->charset = "01234567";
	conv_num(parse);
	print_field(parse, print_unsigned);
	return (1);
}

int		conv_hex_up(t_parse *parse)
{
	parse->nb = va_arg(*parse->ap, unsigned int);
	parse->base = 16;
	parse->charset = "0123456789ABCDEF";
	conv_num(parse);
	print_field(parse, print_unsigned);
	return (1);
}
