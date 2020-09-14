#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ft_printf.h"

void testint(int fd, char *fmt, int arg, int s1, int s2)
{
	char			ft_buff[10024];
	char			pr_buff[10024];
	static int		count = 1;
	int				sf = ft_printf(fmt, arg, s1, s2);
	int				size = read(fd, ft_buff, sf);
	int				sp = snprintf(pr_buff, sizeof(pr_buff), fmt, arg, s1, s2);

	ft_buff[size] = 0;
	if (sf != sp || strcmp(ft_buff, pr_buff))
	{
		dprintf(2, "%d{%s}{%s}{%s}\n", count, fmt, ft_buff, pr_buff);
/*		dprintf(2, "%d\t %d\t %d\t %d", count, sf, sp, arg); */
/*		dprintf(2, "%s\n", fmt); */
	}
	count++;
}

void teststr(char *fmt, const char arg[static 1])
{
	int		sf = ft_printf(fmt, arg);
	int		sp = printf(fmt, arg);

	dprintf(2, "%s\n", fmt);
	if (sf != sp)
		dprintf(2, "%s\n", fmt);

}

const char	*conv = "%pcdiouxX";
const char	*flag = "- 0";
const char	*prec = ".";
const char	*digit = "*0123456789";
void  rand_char(char *fmt, const char *alpha, int *index)
{
	char   c;
	if ((c = alpha[random() % (strlen(alpha) + 1)]))
	{
		fmt[*index] = c;
		(*index)++;
	}
}

void fuzz(int fd)
{
	char	fmt[100];
	int		i = 0;

	rand_char(fmt, conv+1, &i);
	rand_char(fmt, conv+1, &i);
	rand_char(fmt, "%%%%", &i);
	rand_char(fmt, flag, &i);
	rand_char(fmt, flag, &i);
	rand_char(fmt, flag, &i);
	rand_char(fmt, digit, &i);
	rand_char(fmt, digit+1, &i);
	rand_char(fmt, prec, &i);
	rand_char(fmt, digit, &i);
	rand_char(fmt, digit+1, &i);
	rand_char(fmt, conv, &i);
	rand_char(fmt, conv+1, &i);
	rand_char(fmt, conv+1, &i);
	rand_char(fmt, conv+1, &i);
	rand_char(fmt, conv+1, &i);
	fmt[i] = '\0';
	testint(fd, fmt, random() % 101 - 50, random() % 101 - 50, random() % 101 -
		50);
}

int     main(void)
{
	int   fds[2];

	pipe(fds);
	dprintf(2, "%d\n", dup2(fds[1], 1));
	dprintf(2, "%d, %d\n", fds[0], fds[1]);
	/*testint("v%2.xv|", 42); */
	for (int i = 0; i < 30000000; i++)
		fuzz(fds[0]);
	/*
	* testint("{%0i}\n", 0);
	* testint("{%0i}\n", 42);
	* testint("{%7d}\n", 14);
	* testint("{%5c}\n", 'a');
	* testint("{%d}\n", -5);
	* testint("{%.d}\n", 0);
	* testint("{%.u}\n", 0);
	* teststr("{%-10s}\n", __func__);
	*/
}
