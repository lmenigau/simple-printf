/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 12:30:58 by lomeniga          #+#    #+#             */
/*   Updated: 2020/09/14 12:31:32 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int				ft_atoi(char **fmt)
{
	int		nb;
	char	*str;

	str = *fmt;
	nb = 0;
	while (*str && ft_isdigit(*str))
	{
		nb = nb * 10 + (*str - '0');
		str++;
	}
	*fmt = str - 1;
	return (nb);
}

int				parse_field(t_parse *parse)
{
	parse->width = ft_atoi(parse->fmt);
	return (0);
}
