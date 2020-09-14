#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ft_printf.h"

void testint(int fd, char *fmt, int arg, int s1, int s2)
{
	char			ft_buff[1024] = {};
	char			pr_buff[1024] = {};
	static int		count = 1;
	int				sf = ft_printf(fmt, arg, s1, s2);
	int				size = read(fd, ft_buff, sf);
	int				sp = snprintf(pr_buff, sizeof(pr_buff), fmt, arg, s1, s2);

	if (sf != sp || strcmp(ft_buff, pr_buff))
	{
		dprintf(2, "{%s}{%s}{%s}\n", fmt, ft_buff, pr_buff);
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

void  rand_char(char *fmt, const char *alpha, int *index)
{
	fmt[*index] = alpha[random() % strlen(alpha)];
	(*index)++;
}

void fuzz(int fd)
{
	int		fmtsize = random() % 20 + 5;
	char	fmt[100] = {};

	fmt[fmtsize - 1] = '\0';
	char	*conv = "cdiouxX";
	char	*flag = "-0. ";
	char	*digit = "0123456789";
/*
* 	for (int i = 0; i < fmtsize - 1; i++)
* 	{
* 		fmt[i] = random() % 100 + ' ';
* 		if (fmt[i] == '%')
* 			fmt[i] = '\0';
* 	}
*/
	int		i = random() % (fmtsize - 4);
	i = 0;
	fmt[i++] = '%';
	rand_char(fmt, flag, &i);
	rand_char(fmt, flag, &i);
	rand_char(fmt, digit, &i);
	rand_char(fmt, conv, &i);
	testint(fd, fmt, random(), random() % 100, random() % 100);
}

int     main(void)
{
	int   fds[2];

	pipe(fds);
	dprintf(2, "%d\n", dup2(fds[1], 1));
	dprintf(2, "%d, %d\n", fds[0], fds[1]);
	//testint("v%2.xv|", 42);
	for (int i = 0; i < 3000; i++)
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
