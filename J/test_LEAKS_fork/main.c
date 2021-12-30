#include <stdlib.h>
#include <unistd.h>


int main(int ac, char **av, char **env)
{
	char	**str;
	int	pid;

	str = (char **)malloc(sizeof(char*) * 3);
	str[0] = "/usr/bin/echo";
	str[1] = "bonjour";
	str[2] = NULL;

	if (!(pid = fork()))
	{
		execve(str[0], str, env);
	}
	free(str);
	return(0);
}
