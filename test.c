#include "ft_printf.h"
#include <stdlib.h>
#include <string.h>

void testint(char *fmt, int arg)
{
	static int count = 1;
	dprintf(1, "%d{", count);
	int		sf = ft_printf(fmt, arg);
	dprintf(1, "}\n{");
	int		sp = dprintf(1, fmt, arg);
	dprintf(1, "}\n");
	if (sf != sp)
	{
		dprintf(2, "%d, %d, %d:\t", count, sf, sp);
		dprintf(2, "%s\n", fmt);
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

char  rand_char(char *str)
{
	return (str[random() % strlen(str)]);
}

void fuzz(void)
{
	int		fmtsize = random() % 20 + 5;
	char	fmt[fmtsize];

	fmt[fmtsize - 1] = '\0';
	char	*conv = "cdiouxX";
	char	*flag = "-0. ";
	char	*digit = "123456789";
	for (int i = 0; i < fmtsize - 1; i++)
	{
		fmt[i] = random() % 100 + ' ';
		if (fmt[i] == '%')
			fmt[i] = '\0';
	}
	int		i = random() % (fmtsize - 4);
	fmt[i++] = '%';
	if((fmt[i] = rand_char(digit)))
		i++;
	if((fmt[i] = rand_char(flag)))
		i++;
	if((fmt[i] = rand_char(conv)))
		i++;
	/*printf("%s\n", fmt); */
	testint(fmt, random());
}

int     main(void)
{
//	testint("v%2.xv|", 42);
	for (int i = 0; i < 1 << 24; i++)
		fuzz();
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
