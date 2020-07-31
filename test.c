#include "ft_printf.h"

int		main(void)
{
	int		a = 3;
	ft_printf("{%10.5d}\n", 10, 1);
	printf("{%10.5d}\n", 10);
	ft_printf("{%-10s}\n", __func__);
	printf("{%-10s}\n", __func__);
}
