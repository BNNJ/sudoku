#include <stdio.h>

int		main()
{
	int	x = 3;
	int	y = 2;

	printf("%d, %d\n%d, %d\n%d, %d\n%d, %d\n",
		(x / 3) * 3 + (x + 1) % 3, (y / 3) * 3 + (y + 1) % 3,
		(x / 3) * 3 + (x + 1) % 3, (y / 3) * 3 + (y + 2) % 3,
		(x / 3) * 3 + (x + 2) % 3, (y / 3) * 3 + (y + 1) % 3,
		(x / 3) * 3 + (x + 2) % 3, (y / 3) * 3 + (y + 2) % 3);
	return (0);
}
