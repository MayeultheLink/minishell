/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:14:28 by jpauline          #+#    #+#             */
/*   Updated: 2022/01/31 18:37:31 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	wait_all_pid(int *tab, int n)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < n - 1)
	{
		waitpid(tab[i], NULL, 0);
		i++;
	}
	waitpid(tab[i], &status, WEXITSTATUS(status));
	return (status);
}

int	launch_builtin(char **cmd, t_envlst **envlst, int act, int fd)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (my_echo(cmd));
	if (!ft_strcmp(cmd[0], "cd"))
		return (my_cd(cmd, envlst, act));
	if (!ft_strcmp(cmd[0], "pwd"))
		return (my_pwd(fd));
	if (!ft_strcmp(cmd[0], "export"))
		return (my_export(cmd, envlst, act, fd));
	if (!ft_strcmp(cmd[0], "unset"))
		return (my_unset(cmd, envlst, act));
	if (!ft_strcmp(cmd[0], "env"))
		return (my_env(*envlst, fd));
	return (1);
}

int	cmd_manager(t_lst *cmd_lst, char ***env, t_envlst **envlst)
{
	//	char	*underscore;
	int		cmd_nbr;
	int		*tab_fd;
	int		*tab_pid;
	int		i;
	t_lst	*node;
	int		fd_file_in;
	int		fd_file_out;

	cmd_nbr = cmd_count(cmd_lst);

	if (cmd_nbr == 1)
	{
		if (cmd_lst->token->builtin)
		{
	/*	if (cmd_lst->token->path)
		{
			underscore = ft_strcatf("_=", cmd_lst->token->path, 0);
			set_env(envlst, underscore);
			*env = make_envtab(*env, *envlst);
		}*/
			fd_file_out = 1;
			if (cmd_lst->token->redir_out)
				fd_file_out = open(cmd_lst->token->redir_out, O_WRONLY, 0644);
			if (fd_file_out == -1)
			{
				write(2, "Error : cannot open file\n", ft_strlen("Error : cannot open file\n"));
				return (1); //error
			}
			launch_builtin(cmd_lst->token->cmd, envlst, 1, fd_file_out);
			if (cmd_lst->token->redir_out)
				close(fd_file_out);
			return (0); //modif pour prendre en compte la valeur de retour
		}
	}

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
		if (node->token->type_redir_in >= 0)
		{
			if (node->token->type_redir_in == 0)
				fd_file_in = open(node->token->redir_in, O_RDONLY, 0644);
			if (node->token->type_redir_in == 1)
				fd_file_in = node->token->fd_redir_in;
		}
		if (node->token->redir_out)
			fd_file_out = open(node->token->redir_out, O_WRONLY, 0644);
		if (fd_file_in == -1 || fd_file_out == -1)
		{
			write(2, "Error : cannot open file\n", ft_strlen("Error : cannot open file\n"));
			return (1); //error
		}
	//	if (node->token->path)
	//	{
	//		underscore = ft_strcatf("_=", node->token->path, 0);
	//		set_env(envlst, underscore);
	//		*env = make_envtab(*env, *envlst);
	//	}
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
			if (node->token->type_redir_in >= 0)
				dup2(fd_file_in, STDIN_FILENO);
			if (node->token->redir_out)
				dup2(fd_file_out, STDOUT_FILENO);
			//if (node->token->builtin && node->token->cmd)
			//	launch_builtin(node->token->cmd, envlst, 0, 1);
			//else if (node->token->path)
			//	execve(node->token->path, node->token->cmd, *env);
			
			if (!node->token->builtin && node->token->path)
				execve(node->token->path, node->token->cmd, *env);
			if (node->token->builtin && node->token->cmd)
				launch_builtin(node->token->cmd, envlst, 0, 1);
			exit(0);
		}
		else if (tab_pid[i - 1] > 0)
		{
			g_signal = 1;
			if (node->token->path && !ft_strcmp(node->token->path, "./minishell"))
				g_signal = 2;
		}
		if (node->token->type_redir_in >= 0)
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
	int	status;
	status = wait_all_pid(tab_pid, cmd_nbr);

g_signal = 0;
	free(tab_pid);
	return (status);
}
