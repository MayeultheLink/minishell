#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./libft/libft.h"

void	print_split(char **split)
{
	int	i = 0;

	while (split && split[i])
	{
		printf("%d = %s", i, split[i]);
		printf("//\n");
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	char	*path;
	char	**split;
	char	*str;
	char	**split_str;
	int		i;
	int		fret;

	while (1)
	{
		str = readline("prompt> ");
		if (strlen(str) > 0)
		{
			add_history(str);
			split_str = ft_split(str, ' ');
			if (split_str)
			{
//			print_split(split_str);
				if (!strcmp("exit", split_str[0]))
				{
					write(1, "exit\n", 5);
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
				if (split[i] && fork() == 0)
					execve(split[i], split_str, env);
				if (split[i])
					wait(NULL);
			}
			else
			//	printf("Error\n");
				write(1, "Error\n", 6);
		}
	}
	return 0;
}
