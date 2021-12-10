#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include "./libft/libft.h"

int	main(int ac, char **av, char **env)
{
	char	*path;
	char	**split;

	char	*str;
	char **split_str;
	int	i = 0;

	while (1)
	{
	str = readline("prompt> ");
	if (strlen(str) > 0)
	{
		add_history(str);
	split_str = ft_split(str, ' ');
	if (!strcmp("exit", split_str[0]))
	{
		ft_freesplit(split_str);
		free(str);
		break ;
	}
	path = getenv("PATH");
	split = ft_split(path, ':');
	i = 0;
	while (split[i])
	{
	split[i] = strcat(split[i], "/");
	split[i] = strcat(split[i], split_str[0]);
		if (!access(split[i], F_OK))
			break ;
		i++;
	}
	if (fork() == 0)
		execve(split[i], split_str, env);
	else
		wait(NULL);
//	ft_freesplit(split);
//	ft_freesplit(split_str);
//	free(str);
	}
	}
	return 0;
}
