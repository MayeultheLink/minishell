/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 18:43:20 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/05 15:17:23 by mde-la-s         ###   ########.fr       */
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
		c++;
		lst = lst->next;
	}
}

char	*fill_redir(t_lst *lst, int *type_redir, int io)
{
	char	*redir;
	int	i;
	int	j;

//printf("io = %d\n", io);
//printf("str = %s\n", lst->token->str);
	while (io-- > 0 && lst->next)
		lst = lst->next;
//printf("io2 = %d\n", io);
//printf("str = %s\n", lst->token->str);
	if (lst->token->str[1] && (lst->token->str[1] == '<' || lst->token->str[1] == '>'))
		(*type_redir)++;
	redir = malloc(sizeof(char) * (ft_strlen(lst->token->str) - (*type_redir)));
//printf("length = %d\n", (int)ft_strlen(lst->token->str) - (*type_redir));
	if (!redir)
		return (NULL);
	i = (*type_redir);
	j = -1;
	while (lst->token->str[++i])
		redir[++j] = lst->token->str[i];
	redir[++j] = 0;
//printf("redir = %s\n", redir);
	return (redir);
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
		if (in >= 0)
			lst_cmd->token->type_redir_in = 0;
		if (out >= 0)
			lst_cmd->token->type_redir_out = 0;
		if (in >= 0)
			lst_cmd->token->redir_in = fill_redir(ft_lststart(lst), &lst_cmd->token->type_redir_in, in);
//	printf("redir in = %s\n", lst->token->redir_in);
//	printf("out = %d\n", out);
		if (out >= 0)
			lst_cmd->token->redir_out = fill_redir(ft_lststart(lst), &lst_cmd->token->type_redir_out, out);
//	printf("redir out = %s\n", lst->token->redir_out);
		if ((in >= 0 && !lst_cmd->token->redir_in) || (out >= 0 && !lst_cmd->token->redir_out))
			return (NULL);
		if (in < 0)
			lst_cmd->token->redir_in = NULL;
		if (out < 0)
			lst_cmd->token->redir_out = NULL;
		while (lst->next && lst->token->type != PIPE)
			lst = lst->next;
//		if (lst->token->type == PIPE)
//			get_redir(lst->next);
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (ft_lststart(lst));
}
