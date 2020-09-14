/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 12:30:41 by lomeniga          #+#    #+#             */
/*   Updated: 2020/09/14 12:30:44 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		number_len(unsigned long n, int base)
{
	unsigned	len;

	len = 1;
	while (n /= base)
		len++;
	return (len);
}

void	conv_num(t_parse *parse)
{
	if (parse->prec >= 0)
	{
		parse->zero = 0;
		parse->pad = ' ';
	}
	parse->nlen = number_len(parse->nb, parse->base);
	if (!parse->prec && !parse->nb)
		parse->nlen = 0;
	parse->pwidth = parse->nlen;
	if (parse->prec > parse->nlen)
		parse->pwidth = parse->prec;
	parse->padlen = parse->width - parse->pwidth - parse->neg;
}

size_t	ft_strlen(const char *s)
{
	size_t		len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}
