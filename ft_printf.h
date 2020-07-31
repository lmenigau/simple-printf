/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 23:55:51 by lomeniga          #+#    #+#             */
/*   Updated: 2020/07/31 07:33:35 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef		FT_PRINT_H
# define	FT_PRINT_H

# include <stdarg.h>
# include <stdio.h>

int		ft_printf(const char *format, ...);

int		parse_field();
int		conv_char();
int		conv_string();
int		conv_ptr(); 
int		conv_int();
int		conv_uns();
int		conv_hex();
int		conv_pc();
int		flag_min();
int		flag_zero();
int		flag_prec();
int		flag_aste();

typedef struct 	s_parse
{
	va_list			*ap;
	char			**fmt;
	const char		*charset;
	long			nb;
	int				width;
	int				padlen;
	int				prec;
	int				base;
	char			pad;
	_Bool			left;
}				t_parse;

#endif
