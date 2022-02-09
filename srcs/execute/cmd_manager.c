/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 18:14:28 by jpauline          #+#    #+#             */
/*   Updated: 2022/02/09 16:20:28 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_man(t_manag *man)
{
	close_all_fd(man->tab_fd, man->cmd_nbr - 1);
	free(man->tab_fd);
	free(man->tab_pid);
	free(man);
}

void	execute_parent(t_lst *node, t_manag *man)
{
	g_signal = 1;
	if (node->token->path && !ft_strcmp(node->token->path, "./minishell"))
		g_signal = 2;
	if (node->token->type_ri >= 0)
		close(man->fd_file_in);
	if (node->token->redir_out)
		close(man->fd_file_out);
}

void	execute_fork(t_manag *man, t_lst *node, char **env, t_envlst **envlst)
{
	signal(SIGQUIT, SIG_DFL);
	if (man->cmd_nbr > 1 && man->i != man->cmd_nbr)
		dup2(man->tab_fd[(man->i - 1) * 2 + 1], STDOUT_FILENO);
	if (man->cmd_nbr > 1 && man->i != 1)
		dup2(man->tab_fd[(man->i - 2) * 2], STDIN_FILENO);
	close_all_fd(man->tab_fd, man->cmd_nbr - 1);
	if (node->token->type_ri >= 0)
		dup2(man->fd_file_in, STDIN_FILENO);
	if (node->token->redir_out)
		dup2(man->fd_file_out, STDOUT_FILENO);
	if (check_path(node->token->path))
		exit(126);
	if (!node->token->path)
		exit(127);
	if (!node->token->builtin && node->token->path)
		execve(node->token->path, node->token->cmd, env);
	if (node->token->builtin && node->token->cmd)
		exit(launch_builtin(node, envlst, 0, 1));
	exit(0);
}

int	builtin(t_lst *cmd_lst, t_envlst **envlst)
{
	int		fd_file_out;
	int		ret;
	char	*str;

	fd_file_out = 1;
	if (cmd_lst->token->type_redir_out == 0)
		fd_file_out = open(cmd_lst->token->redir_out, O_WRONLY | O_TRUNC, 0644);
	if (cmd_lst->token->type_redir_out == 1)
		fd_file_out = open(cmd_lst->token->redir_out,
				O_WRONLY | O_APPEND, 0644);
	if (fd_file_out == -1)
		return (write(2, "Error : cannot open file\n", 25), 1);
	str = ft_strcatf("_=", cmd_lst->token->path, 0);
	if (!str || set_env(envlst, str))
		return (1);
	free(str);
	ret = launch_builtin(cmd_lst, envlst, 1, fd_file_out);
	if (cmd_lst->token->redir_out)
		close(fd_file_out);
	return (ret);
}

int	cmd_manager(t_lst *node, char ***env, t_envlst **envlst)
{
	t_manag	*man;

	man = init_man(node);
	if (man->cmd_nbr == 1 && node->token->builtin)
		return (free(man), builtin(node, envlst));
	if (init_tab_fd(&man->tab_fd, man->cmd_nbr, &man->tab_pid))
		return (free(man), 1);
	while (man->i <= man->cmd_nbr)
	{
		redirections(&man->fd_file_in, &man->fd_file_out, node);
		if (man->fd_file_in == -1 || man->fd_file_out == -1)
			return (free_man(man),
				write(2, "Error : cannot open file\n", 25), 1);
		man->tab_pid[man->i - 1] = fork();
		if (man->tab_pid[man->i - 1] == -1)
			return (free_man(man), write(2, "Failed fork\n", 12), 1);
		*env = m_envp(*env, envlst, node);
		if (man->tab_pid[man->i - 1] == 0 && *env)
			execute_fork(man, node, *env, envlst);
		else if (man->tab_pid[man->i - 1] > 0)
			execute_parent(node, man);
		node = node->next;
		man->i++;
	}
	return (free_and_wait(man));
}
