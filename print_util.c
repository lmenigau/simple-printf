/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 12:31:08 by lomeniga          #+#    #+#             */
/*   Updated: 2020/09/14 12:31:12 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_buf(t_buf *buf, char c)
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

void	ft_putnbr_base_prec(t_buf *buf, unsigned long n, const char base[],
	int len)
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

void	pad_char(t_buf *buf, int n, char c)
{
	while (n > 0)
	{
		write_buf(buf, c);
		n--;
	}
}

void	print_field(t_parse *parse, void (f)(t_parse *))
{
	if (parse->zero && parse->neg)
		write_buf(parse->buf, '-');
	if (parse->left)
		f(parse);
	pad_char(parse->buf, parse->padlen, parse->pad);
	if (!parse->left)
		f(parse);
}
