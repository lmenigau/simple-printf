/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 12:30:47 by lomeniga          #+#    #+#             */
/*   Updated: 2020/09/14 12:30:49 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		flag_aste(t_parse *parse)
{
	parse->width = va_arg(*parse->ap, int);
	if (parse->width < 0)
	{
		parse->width = -parse->width;
		parse->left = 1;
		parse->zero = 0;
		parse->pad = ' ';
	}
	return (0);
}

int		flag_min(t_parse *parse)
{
	parse->left = 1;
	parse->zero = 0;
	parse->pad = ' ';
	return (0);
}

int		flag_prec(t_parse *parse)
{
	(*parse->fmt)++;
	if (**parse->fmt == '*')
	{
		parse->prec = va_arg(*parse->ap, int);
	}
	else
		parse->prec = ft_atoi(parse->fmt);
	return (0);
}

int		flag_zero(t_parse *parse)
{
	if (!parse->left)
	{
		parse->zero = 1;
		parse->pad = '0';
	}
	return (0);
}

int		flag_space(t_parse *parse)
{
	parse->space = 1;
	return (0);
}
