/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 12:30:35 by lomeniga          #+#    #+#             */
/*   Updated: 2020/09/14 12:30:37 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		conv_char(t_parse *parse)
{
	parse->padlen = parse->width - 1;
	print_field(parse, print_char);
	return (1);
}

int		conv_pc(t_parse *parse)
{
	parse->padlen = parse->width - 1;
	print_field(parse, print_pc);
	return (1);
}

int		conv_ptr(t_parse *parse)
{
	parse->nb = va_arg(*parse->ap, long);
	parse->hash = 1;
	parse->base = 16;
	parse->charset = "0123456789abcdef";
	conv_num(parse);
	parse->padlen -= 2;
	if (parse->hash && parse->zero)
	{
		write_buf(parse->buf, '0');
		write_buf(parse->buf, 'x');
	}
	print_field(parse, print_unsigned);
	return (1);
}

int		conv_string(t_parse *parse)
{
	int		len;

	parse->str = va_arg(*parse->ap, char *);
	if (parse->str == NULL)
		parse->str = "(null)";
	len = ft_strlen(parse->str);
	parse->padlen = parse->width;
	if (parse->prec >= 0 && parse->prec < len)
		len = parse->prec;
	parse->padlen -= len;
	print_field(parse, print_str);
	return (1);
}
