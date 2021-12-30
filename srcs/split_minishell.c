/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:07:24 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/30 19:18:03 by mde-la-s         ###   ########.fr       */
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

t_token	*malloc_token(int end, int beg, int c)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = malloc(sizeof(char) * (end - beg - c) + 1);
	if (!token->str)
		return (NULL);
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
		if ((str[beg + i] == '"' || str[beg + i] == '\'')
				&& control[beg + i] == '0')
			c++;
	token = malloc_token(end, beg, c);
	if (!token)
		return (NULL);
	c = beg - 1;
	i = 0;
	while (++c + i < end)
	{
		while ((str[c + i] == '"' || str[c + i] == '\'')
				&& control[c + i] == '0')
			i++;
		token->str[c - beg] = str[c + i];
	}
	token->str[c - beg] = 0;
	while (str[beg] != token->str[0])
		beg++;
	token->type = get_type(token, control[beg]);
	return (token);
}

t_lst	*lst_add(t_lst *lst, t_token *token)
{
	t_lst	*lst_start;

	lst_start = lst;
	if (!lst)
	{
		lst = malloc(sizeof(t_lst));
		if (!lst)
			return (NULL);
		lst->token = token;
		lst->previous = NULL;
		lst->next = NULL;
		return (lst);
	}
	while (lst->next)
		lst = lst->next;
	lst->next = malloc(sizeof(t_lst));
	if (!lst->next)
		return (NULL);
	lst->next->previous = lst;
	lst->next->token = token;
	lst->next->next = NULL;
	return (lst_start);
}

t_lst	*split_minishell(char *str, char *control)
{
	t_lst	*lst;
	int	beginning;
	int	end;

	lst = NULL;
	beginning = 0;
	while (str[beginning] && str[beginning] == ' ')
		beginning++;
	end = beginning;
	while (str[++end])
	{
		if ((str[end] == ' ' || ((str[end] == '<' || str[end] == '>') && str[end - 1] != str[end])) 
				&& control[end] == '0')
		{
			lst = lst_add(lst, get_token(str, control, beginning, end));
			beginning = end;
			while (str[beginning] == ' ')
				beginning++;
			end = beginning;
		}
	}
	if (str[beginning])
		lst = lst_add(lst, get_token(str, control, beginning, end));
	lst = parse_lst(lst);
	return (ft_lststart(lst));
}
