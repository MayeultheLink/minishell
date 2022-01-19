/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:07:24 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/19 17:26:21 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type(t_token *token, char c)
{
	if (token->str[0] == '|' && c == '0')
		return (PIPE);
	else if ((token->str[0] == '<' || token->str[0] == '>') && c == '0')
		return (REDIR);
	else
		return (CMD);
}

t_token	*init_token(int end, int beg, int c)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = NULL;
	token->path = NULL;
	token->cmd = NULL;
	token->redir_in = NULL;
	token->redir_out = NULL;
	token->builtin = 0;
	token->type_redir_in = -1;
	token->type_redir_out = -1;
	token->type = -1;
	token->str = malloc(sizeof(char) * ((end - beg - c) + 1));
	if (!token->str)
	{
		free(token);
		return (NULL);
	}
	return (token);
}

t_token	*get_token(char *str, char *control, int beg, int end)
{
	t_token	*token;
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (beg + ++i < end)
	{
		if ((str[beg + i] == '"' || str[beg + i] == '\'')
				&& control[beg + i] == '0')
			c++;
	}
	if (c == (int)ft_strlen(str))
		return (NULL);
	token = init_token(end, beg, c);
	if (!token)
		return (NULL);
	c = beg - 1;
	i = 0;
	while (++c + i < end)
	{
		while ((str[c + i] == '"' || str[c + i] == '\'')
				&& control[c + i] == '0')
			i++;
		if (c + i >= end)
			break ;
		token->str[c - beg] = str[c + i];
	}
	token->str[c - beg] = 0;
	token->type = get_type(token, control[beg]);
	return (token);
}

t_lst	*lst_add(t_lst *lst, t_token *token)
{
	t_lst	*tmp;

	tmp = lst;
	if (!token)
	{
		freelst(lst);
		return (NULL);
	}
	if (!lst)
	{
		lst = malloc(sizeof(t_lst));
		if (!lst)
		{
			free(token);
			token = NULL;
			return (NULL);
		}
		lst->token = token;
		lst->previous = NULL;
		lst->next = NULL;
		return (lst);
	}
	while (lst->next)
		lst = lst->next;
	lst->next = malloc(sizeof(t_lst));
	if (!lst->next)
	{
		freelst(tmp);
		free(token);
		token = NULL;
		return (NULL);
	}
	lst->next->previous = lst;
	lst->next->token = token;
	lst->next->next = NULL;
	return (lst);
}

t_lst	*split_minishell(char *str, char *control, char **env)
{
	char	*new;
	t_lst	*lst;
	int		beginning;
	int		end;

	if (!control)
		return (NULL);
	lst = NULL;
	beginning = 0;
	new = treat_dollar(str, control, env, 1);
	while (new && new[beginning] && new[beginning] == ' ')
		beginning++;
	if (!new || !new[beginning])
	{
		free(control);
		return (NULL);
	}
	end = beginning;
	while (new[++end])
	{
		if (control[end] == '0' && (new[end] == ' ' || ((new[end] == '<' || new[end] == '>')
				&& new[end - 1] != new[end]) || new[end] == '|' || new[end - 1] == '|'))
		{
			lst = lst_add(lst, get_token(new, control, beginning, end));
			if (!lst)
			{
				free(new);
				free(control);
				return (NULL);
			}
			beginning = end;
			while (new[beginning] && new[beginning] == ' ')
				beginning++;
			end = beginning;
		}
	}
	if (new[beginning])
		lst = lst_add(lst, get_token(new, control, beginning, end));
	free(control);
	free(new);
	if (!lst)
		return (NULL);
	return (ft_lststart(lst));
}
