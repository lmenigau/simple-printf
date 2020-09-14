/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 23:55:51 by lomeniga          #+#    #+#             */
/*   Updated: 2020/09/14 12:50:10 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int				ft_printf(const char *format, ...);

typedef struct	s_buf
{
	size_t	total;
	char	buf[1024];
	int		index;

}				t_buf;

typedef struct	s_parse
{
	va_list		*ap;
	char		**fmt;
	const char	*charset;
	char		*str;
	t_buf		*buf;
	long		nb;
	int			width;
	int			pwidth;
	int			padlen;
	int			nlen;
	int			prec;
	int			base;
	char		pad;
	_Bool		zero;
	_Bool		left;
	_Bool		neg;
	_Bool		hash;
	_Bool		space;
}				t_parse;

void			print_field(t_parse *parse, void (f)(t_parse *));

int				ft_atoi(char **fmt);
size_t			ft_strlen(const char *s);
void			ft_putnbr_base_prec(t_buf *buf, unsigned long n,
		const char base[], int len);

void			pad_char(t_buf *buf, int n, char c);
void			print_field(t_parse *parse, void (f)(t_parse *));
void			write_buf(t_buf *buf, char c);
void			print_unsigned(t_parse *parse);
void			print_signed(t_parse *parse);
void			print_pc(t_parse *parse);
void			print_char(t_parse *parse);
void			print_str(t_parse *parse);

int				parse_field(t_parse *parse);
int				number_len(unsigned long n, int base);

void			conv_num(t_parse *parse);
int				conv_char(t_parse *parse);
int				conv_string(t_parse *parse);
int				conv_ptr(t_parse *parse);
int				conv_int(t_parse *parse);
int				conv_uns(t_parse *parse);
int				conv_hex(t_parse *parse);
int				conv_hex_up(t_parse *parse);
int				conv_pc(t_parse *parse);
int				conv_octal(t_parse *parse);

int				flag_space(t_parse *parse);
int				flag_min(t_parse *parse);
int				flag_zero(t_parse *parse);
int				flag_prec(t_parse *parse);
int				flag_aste(t_parse *parse);

#endif
