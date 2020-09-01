#include "ft_printf.h"

int		main(void)
{
	int		a = 3;
	ft_printf("{%.d}\n", 0);
	printf("{%.d}\n", 0);
	ft_printf("{%-10s}\n", __func__);
	printf("{%-10s}\n", __func__);
}
