/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:14:28 by jpauline          #+#    #+#             */
/*   Updated: 2022/01/06 16:51:00 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>

#include "minishell.h"

int	cmd_count(t_lst *cmd_lst)
{
	int		i;
	t_lst	*lst;

	i = 0;
	lst = cmd_lst;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	*create_tab_fd(int n)
{
	int	*tab;
	int	i;

	tab = (int *)malloc(sizeof(int) * 2 * n);
	i = -1;
	while (++i < n)
	{
		if (pipe(tab + (i * 2)) == -1)
			return (NULL);
	}
	return (tab);
}

int	*create_tab_pid(int n)
{
	int	*tab;

	tab = (int *)malloc(sizeof(int) * (n));
	return (tab);
}

void	close_all_fd(int *tab_fd, int n)
{
	int	i;

	i = 0;
	while (i < (2 * n))
	{
		close(tab_fd[i]);
		i++;
	}
}

void	wait_all_pid(int *tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		waitpid(tab[i], NULL, 0);
		i++;
	}
}

int	cmd_manager(t_lst *cmd_lst, char **env)
{
	int		cmd_nbr;
	int		*tab_fd;
	int		*tab_pid;
	int		i;
	t_lst	*node;
	int		fd_file_in;
	int		fd_file_out;

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
			return (1); //error
		tab_pid[i - 1] = fork();
		if (tab_pid[i - 1] == -1)
			return (1); //error
		if (tab_pid[i - 1] == 0)
		{
			if (cmd_nbr > 1 && i != cmd_nbr)
				dup2(tab_fd[(i - 1) * 2 + 1], STDOUT_FILENO);
			if (cmd_nbr > 1 && i != 1)
				dup2(tab_fd[(i - 2) * 2], STDIN_FILENO);
			close_all_fd(tab_fd, cmd_nbr - 1);
			if (node->token->redir_in)
				dup2(fd_file_in, STDIN_FILENO);
			if (node->token->redir_out)
				dup2(fd_file_out, STDOUT_FILENO);
			execve(node->token->cmd[0], node->token->cmd, env);
		}
		if (node->token->redir_in)
			close(fd_file_in);
		if (node->token->redir_out)
			close(fd_file_out);
		node = node->next;
		i++;
	}
	if (cmd_nbr > 1)
	{	
		close_all_fd(tab_fd, cmd_nbr - 1);
		free(tab_fd);
	}
	wait_all_pid(tab_pid, cmd_nbr);
	free(tab_pid);
	return (0);
}
