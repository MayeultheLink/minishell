/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:46:05 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/04 17:50:57 by mde-la-s         ###   ########.fr       */
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

t_manag	*init_man(void)
{
	t_manag	*man;

	man = malloc(sizeof(t_manag));
	if (!man)
		return (write(2, "Failed malloc\n", 14), NULL);
	man->cmd_nbr = 0;
	man->tab_fd = NULL;
	man->tab_pid = NULL;
	man->fd_file_in = -2;
	man->fd_file_out = -2;
	man->i = 1;
	return (man);
}

void	redirections(int *fd_file_in, int *fd_file_out, t_lst *node)
{
	if (node->token->type_redir_in >= 0)
	{
		if (node->token->type_redir_in == 0)
			*fd_file_in = open(node->token->redir_in, O_RDONLY, 0644);
		if (node->token->type_redir_in == 1)
			*fd_file_in = node->token->fd_redir_in;
	}
	if (node->token->type_redir_out == 0)
		*fd_file_out = open(node->token->redir_out, O_WRONLY | O_TRUNC, 0644);
	if (node->token->type_redir_out == 1)
		*fd_file_out = open(node->token->redir_out, O_WRONLY | O_APPEND, 0644);
}

int	init_tab_fd(int **tab_fd, int cmd_nbr, int **tab_pid)
{
	if (cmd_nbr > 1)
		*tab_fd = create_tab_fd(cmd_nbr - 1);
	if (cmd_nbr > 1 && *tab_fd == NULL)
		return (write(2, "Failure to generate fd\n", 23), 1);
	*tab_pid = create_tab_pid(cmd_nbr);
	return (0);
}

int	free_and_wait(t_manag *man)
{
	int	status;

	if (man->cmd_nbr > 1)
	{	
		close_all_fd(man->tab_fd, man->cmd_nbr - 1);
		free(man->tab_fd);
	}
	status = wait_all_pid(man->tab_pid, man->cmd_nbr);
	g_signal = 0;
	free(man->tab_pid);
	free(man);
	return (status);
}
