#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void	handler()
{
	printf("oui\n");
}

void	test()
{
	while (1)
	{}
	signal(SIGINT, handler);
}

int	try()
{
	return (write(2, "lol\n", 4), 1);
}

int	main()
{
	printf("%d\n", try());
	return (0);
}
