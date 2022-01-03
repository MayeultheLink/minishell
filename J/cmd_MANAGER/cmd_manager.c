/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:14:28 by jpauline          #+#    #+#             */
/*   Updated: 2022/01/03 20:49:40 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>

#include "../../headers/minishell.h"

int cmd_count(t_lst *cmd_lst)
{
	int	i;
	t_lst	*lst;

	i = 0;
	lst = cmd_lst;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	**create_tab_fd(int n)
{
	int	fd[2];
	int	**tab;
	int	i;

	tab = (int **)malloc(sizeof(fd) * (n + 1));
	i = 0;
	while (i < n)
	{
		if (pipe(tab[i]) == -1)
			return (NULL);
	}
	tab[n][0] = -1;
	tab[n][1] = -1;
	return (tab);
}

int	*create_tab_pid(int n)
{
	int	*tab;
	
	tab = (int *)malloc(sizeof(int) * (n));
	return (tab);
}

void	close_all_fd(int **tab_fd)
{
	int	i;

	i = 0;
	while (tab_fd[i][0] != -1 && tab_fd[i][1] != -1)
	{
		close(tab_fd[i][0]);
		close(tab_fd[i][1]);
		i++;
	}
}

void	wait_all_pid(int *tab, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		waitpid(tab[i], NULL, 0);
		i++;
	}
}

int cmd_manager(t_lst *cmd_lst)
{
	int	cmd_nbr;
	int	**tab_fd;
	int	*tab_pid;
	int	i;
	t_lst	*node;
	int	fd_file_in;
	int	fd_file_out;
//	char	**cmd;

	cmd_nbr = cmd_count(cmd_lst);
	tab_fd = NULL;
	if (cmd_nbr > 1)
		tab_fd = create_tab_fd(cmd_nbr - 1);
	if (cmd_nbr > 1 && tab_fd == NULL)
		return (1); /*error*/
	tab_pid = create_tab_pid(cmd_nbr);
	i = 1;
	node = cmd_lst;
	while (i <= cmd_nbr)
	{
		fd_file_in = -2;
		fd_file_out = -2;
		if (node->token->redir_in)
			fd_file_in = open(node->token->redir_in, O_RDONLY, 0666);
		if (node->token->redir_out)
			fd_file_out = open(node->token->redir_out, O_WRONLY, 0666);
		if (fd_file_in == -1 || fd_file_out == -1)
				return (1); /*error*/
//		cmd = node->cmd;
		tab_pid[i - 1] = fork();
		if (tab_pid[i - 1] == -1)
			return (1); /*error*/
		else if (tab_pid[i - 1] == 0)
		{
			if (cmd_nbr > 1 && i != cmd_nbr)
				dup2(tab_fd[i][1], STDOUT_FILENO);
			if (cmd_nbr > 1 && i != 1)
				dup2(tab_fd[i - 1][0], STDIN_FILENO);
			close_all_fd(tab_fd);
			if (node->token->redir_in)
				dup2(fd_file_in, STDIN_FILENO);
			if (node->token->redir_out)
				dup2(fd_file_out, STDOUT_FILENO);
			execve(node->token->cmd[0], node->token->cmd, env);
		}
		close(fd_file_in);
		close(fd_file_out);
		node = node->next;
		i++;
	}
	close_all_fd(tab_fd);
	wait_all_pid(tab_pid, cmd_nbr);
	free_tab(tab_fd);
	free_tab(tab_fd);
}

int main()
{
	return (0);
}
