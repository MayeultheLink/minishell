#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "./libft/libft.h"

char *init_cmd(char* cmd, char** s1, char** s2, int i, int j)
{
	char* new;

	new = (char*)malloc(sizeof(char) * (strlen(s1[i]) + strlen(s2[j]) + 2));
	if (cmd)
		free(cmd);
	new[0] = 0;
	return(new);
}

void freetab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	main(int ac, char **av, char **env)
{
	char	*path;
	char	**split;
	char	*cmd;
	char	*str;
	char	**split_str;
	int		i;
	int		fret;

	cmd = NULL;
	while (1)
	{
		str = readline("prompt> ");
		if (strlen(str) > 0)
		{
			add_history(str);
			split_str = ft_split(str, ' ');
			if (!strcmp("exit", split_str[0]))
				break ;
			path = getenv("PATH");
			split = ft_split(path, ':');

			i = 0;
			while(split[i])
			{
				printf("i=%d, orig = %s\n", i, split[i]);
				i++;
			}

			int fd[2];
			if (pipe(fd) == -1)
				return 1;
			int fd2[2];
			if (pipe(fd2) == -1)
				return 1;

			i = 0;
			while (split[i])
			{
				cmd  = init_cmd(cmd, split, split_str, i, 0);
				//split[i] = strcat(split[i], "/");
				//split[i] = strcat(split[i], split_str[0]);
				cmd = strcat(cmd, split[i]);
				cmd = strcat(cmd, "/");
				cmd = strcat(cmd, split_str[0]);
printf("s  : %s, i : %d\n", cmd, i);
				if (!access(cmd, F_OK))
					break ;
//printf("s : %s, i : %d\n", cmd, i);
				i++;
			}
			int	pid1;
			if (split[i] && (!(pid1 = fork())))
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				close(fd2[0]);
				close(fd2[1]);
				//int		fd_file;
				//fd_file = open("toto", O_WRONLY | O_CREAT, 0666);
				//dup2(fd_file, STDOUT_FILENO);
				char 	*cmd1[2];
				cmd1[0]= cmd;
				cmd1[1]= NULL;
				execve(cmd, cmd1, env);
			}
			
			i=0;
			while (split[i])
			{
				cmd  = init_cmd(cmd, split, split_str, i, 1);
				//split[i] = strcat(split[i], "/");
				//split[i] = strcat(split[i], split_str[1]);
				cmd = strcat(cmd, split[i]);
				cmd = strcat(cmd, "/");
				cmd = strcat(cmd, split_str[1]);
printf("s : %s, i : %d\n", cmd, i);
				if (!access(cmd, F_OK))
					break ;
				i++;
			}
			int	pid2;
			if (split[i] && (!(pid2 = fork())))
			{
		//	sleep(3);	
				dup2(fd2[1], STDOUT_FILENO);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
				close(fd[1]);
				close(fd2[0]);
				close(fd2[1]);
				//int		fd_file;
				//fd_file = open("bob", O_WRONLY | O_CREAT, 0666);
				//dup2(fd_file, STDOUT_FILENO);
				char *cmd2[3];
				cmd2[0]= cmd;
//				cmd2[1]= "test";
//				cmd2[2]= NULL;
				cmd2[1]= NULL;
				execve(cmd, cmd2, env);
			}
		
			i=0;
			while (split[i])
			{
				cmd  = init_cmd(cmd, split, split_str, i, 2);
				//split[i] = strcat(split[i], "/");
				//split[i] = strcat(split[i], split_str[1]);
				cmd = strcat(cmd, split[i]);
				cmd = strcat(cmd, "/");
				cmd = strcat(cmd, split_str[2]);
printf("s: %s, i : %d\n", cmd, i);
				if (!access(cmd, F_OK))
					break ;
				i++;
			}
			int	pid3;
			if (split[i] && (!(pid3 = fork())))
			{
		//	sleep(6);	
				dup2(fd2[0], STDIN_FILENO);
				close(fd[0]);
				close(fd[1]);
				close(fd2[0]);
				close(fd2[1]);
				//int		fd_file;
				//fd_file = open("bob", O_WRONLY | O_CREAT, 0666);
				//dup2(fd_file, STDOUT_FILENO);
				char *cmd3[2];
				cmd3[0]= cmd;
				cmd3[1]= NULL;
				execve(cmd, cmd3, env);
			}
			
			i = 0;
			if (split[i])
			{	
				close(fd[0]);
				close(fd[1]);
				close(fd2[0]);
				close(fd2[1]);
				waitpid(pid1, NULL, 0);
				waitpid(pid2, NULL, 0);
				waitpid(pid3, NULL, 0);
			}
		}
	}
	if (cmd)
		free(cmd);
	if (split)
		freetab(split);
	return 0;
}
