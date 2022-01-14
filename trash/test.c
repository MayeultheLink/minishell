#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av, char **env)
{
char	**str;
char	test[3];
char	*tmp;

test[0] = 'a';
test[1] = 'b';
test[2] = 0;

tmp = malloc(sizeof(char));
	str = malloc(sizeof(char*) * 2);
	str[1] = NULL;
	str[0] = readline("hue> ");
printf("parent = %p\n", &str);
int	i;
	if (!(i = fork()))
{
//char	*tmp2;
//tmp = NULL;
//tmp2 = malloc(sizeof(char));
printf("enfant = %p\n", &str);
//printf("t enfant = %s\n", test);
//test[0] = 'b';
//printf("t enfant = %s\n", test);
//printf("enfant = %p\n", &test);
	//	execve(str[0], str, env);
free(tmp);
usleep(1000);
printf("test\n");
}
else if (i > 0)
	{
usleep(100);
//printf("t parent = %s\n", test);
//printf("parent = %p\n", &test);

}
	wait(NULL);
	free(str[0]);
	free(str);
free(tmp);
	return (0);
}
