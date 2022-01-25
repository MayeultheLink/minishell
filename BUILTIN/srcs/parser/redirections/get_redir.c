/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:43:20 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/25 12:51:45 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_redir(t_lst *lst, int *i, int *o)
{
	t_lst	*tmp;
	int		c;

	*i = -1;
	*o = -1;
	tmp = ft_lststart(lst);
	c = 0;
	while (tmp != lst)
	{
		c++;
		tmp = tmp->next;
	}
	while (lst && lst->token->type != PIPE)
	{
		if (lst->token->type == REDIR)
		{
			if (lst->token->str[0] == '<')
				*i = c;
			else if (lst->token->str[0] == '>')
				*o = c;
		}
		c++;
		lst = lst->next;
	}
}

char	*fill_redir(t_lst *lst, int *type_redir, int *fd_redir_in, int io)
{
	char	*redir;
	int		i;
	int		j;

	*type_redir = 0;
	while (io-- > 0 && lst->next)
		lst = lst->next;
	if (lst->token->str[1]
		&& (lst->token->str[1] == '<' || lst->token->str[1] == '>'))
		(*type_redir)++;
	if (lst->token->str[1] == '<')
	{
		*fd_redir_in = lst->token->fd_redir_in;
		return (NULL);
	}
	redir = malloc(sizeof(char) * (ft_strlen(lst->token->str) - (*type_redir)));
	if (!redir)
		return (NULL);
	i = (*type_redir);
	j = -1;
	while (lst->token->str[++i])
		redir[++j] = lst->token->str[i];
	redir[++j] = 0;
	return (redir);
}

int	get_redir(t_lst *lst)
{
	t_lst	*lst_cmd;
	int		in;
	int		out;

	while (lst)
	{
		find_redir(lst, &in, &out);
		lst_cmd = lst;
		while (lst_cmd->token->type != CMD)
			lst_cmd = lst_cmd->next;
		if (in >= 0)
			lst_cmd->token->redir_in = fill_redir(ft_lststart(lst),
					&lst_cmd->token->type_redir_in,
					&lst_cmd->token->fd_redir_in, in);
		if (out >= 0)
			lst_cmd->token->redir_out = fill_redir(ft_lststart(lst),
					&lst_cmd->token->type_redir_out, 0, out);
		if ((lst_cmd->token->type_redir_in == 0 && !lst_cmd->token->redir_in)
			|| (out >= 0 && !lst_cmd->token->redir_out))
			return (write(2, "Failed malloc\n", 14), 0);
		while (lst->next && lst->token->type != PIPE)
			lst = lst->next;
		lst = lst->next;
	}
	return (1);
}
