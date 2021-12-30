/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:43:20 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/30 19:01:09 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_redir(t_lst *lst, int *i, int *o)
{
	t_lst	*tmp;
	int	c;

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
		else
			c++;
		lst = lst->next;
	}
}

int	fill_redir(t_lst *lst, char **redir, int *type_redir, int io)
{
	int	i;
	int	j;

	if (io == -1)
		return (1);
	while (io--)
		lst = lst->next;
	if (lst->token->str[1] == '<' || lst->token->str[1] == '>')
		*type_redir = 1;
	*redir = malloc(sizeof(char) * ft_strlen(lst->token->str) - *type_redir);
	if (!*redir)
		return (0);
	i = *type_redir;
	j = -1;
	while (lst->token->str[++i])
		(*redir)[++j] = lst->token->str[i];
	(*redir)[++j] = 0;
	return (1);
}

t_lst	*get_redir(t_lst *lst)
{
	t_lst	*lst_cmd;
	int	in;
	int	out;

	while (lst)
	{
		in = -1;
		out = -1;
		find_redir(lst, &in, &out);
		lst_cmd = lst;
		while (lst_cmd->token->type != CMD)
			lst_cmd = lst_cmd->next;
		if (!fill_redir(lst, &lst_cmd->token->redir_in, &lst->token->type_redir_in, in)
			|| !fill_redir(lst, &lst_cmd->token->redir_out, &lst->token->type_redir_out, out))
			return (NULL);
		while (lst->next && lst->token->type != PIPE)
			lst = lst->next;
		lst = lst->next;
	}
	return (ft_lststart(lst));
}
