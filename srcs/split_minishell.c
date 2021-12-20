/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:07:24 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/20 13:06:45 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type(t_token *token)
{
	if (token->str[0] == '|')
		return (PIPE);
	else if (token->str[0] == '<' || token->str[0] == '>')
		return (REDIR);
	else if (ft_isalpha(token->str[0])
			&& (token->previous && (token->previous.type == CMD
					|| token->previous.type == ARG)))
		return (ARG);
	else
		return (CMD);
}

t_token	*get_token(char *str, char *control, int beginning, int end)
{
	t_token	token;
	int	i;
	int	c;

	i = -1;
	c = 0;
	while (beginning + ++i < end)
		if ((str[beginning + i] == '"' || str[beginning + i] == '\'') && control[beginning + i] == '0')
			c++;
	token.str = malloc(sizeof(char) * (end - beginning - c) + 1);
	if (!token.str)
		return (NULL);
	while (beginning < end)
	{
		while ((str[beginning] == '"' || str[beginning] == '\'') && control[beginning] == '0')
			beginning++;
		token.str[beginning] == str[beginning];
		beginning++;
	}
	token.str[beginning] = 0;
	token.type = get_type(token);
	return (token);
}

t_lst	*lst_add(t_lst *lst, t_token token)
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
	t_token	token;
	int	beginning;
	int	end;

	lst = NULL;
	beginning = 0;
	end = -1;
	while (str[++end])
		if (str[end] == ' ' && str[end - 1] != ' ' && control[end] == '0')
		{
			lst = lst_add(lst, get_token(str, control, beginning, end));
			beginning = end + 1;
		}
	return (lst);
}
