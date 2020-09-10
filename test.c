#include "ft_printf.h"

void testint(char *fmt, int arg)
{
	ft_printf(fmt, arg);
	printf(fmt, arg);
}

void teststr(char *fmt, const char arg[static 1])
{
	ft_printf(fmt, arg);
	printf(fmt, arg);
}
int		main(void)
{
	int		a = 3;
	testint("{%7d}\n", 14);
	testint("{%5c}\n", 'a');
	testint("{%d}\n", -5);
	testint("{%.d}\n", 0);
	testint("{%.u}\n", 0);
	teststr("{%-10s}\n", __func__);
}
