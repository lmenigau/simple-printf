/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 12:31:04 by lomeniga          #+#    #+#             */
/*   Updated: 2020/09/14 12:31:05 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_unsigned(t_parse *parse)
{
	if (parse->hash && !parse->zero)
	{
		write_buf(parse->buf, '0');
		write_buf(parse->buf, 'x');
	}
	pad_char(parse->buf, parse->pwidth - parse->nlen, '0');
	if (parse->prec || parse->nb)
		ft_putnbr_base_prec(parse->buf, parse->nb, parse->charset, parse->base);
}

void	print_signed(t_parse *parse)
{
	if (parse->neg && !parse->zero)
		write_buf(parse->buf, '-');
	else if (parse->space && !parse->zero)
		write_buf(parse->buf, ' ');
	pad_char(parse->buf, parse->pwidth - parse->nlen - (parse->zero &&
		parse->neg), '0');
	if (parse->prec || parse->nb)
		ft_putnbr_base_prec(parse->buf, parse->nb, parse->charset, parse->base);
}

void	print_str(t_parse *parse)
{
	int		i;

	i = 0;
	while ((parse->prec > 0 && i < parse->prec && parse->str[i])
			|| (parse->prec < 0 && parse->str[i]))
	{
		write_buf(parse->buf, parse->str[i]);
		i++;
	}
}

void	print_char(t_parse *parse)
{
	unsigned char	c;

	c = va_arg(*parse->ap, int);
	write_buf(parse->buf, c);
}

void	print_pc(t_parse *parse)
{
	write_buf(parse->buf, '%');
}
