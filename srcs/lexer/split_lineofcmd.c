/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lineofcmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:07:24 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/01 18:59:39 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*lst_add(t_lst *lst, t_token *token)
{
	if (!token)
		return (NULL);
	if (!lst)
	{
		lst = malloc(sizeof(t_lst));
		if (!lst)
			return (write(2, "Failed malloc\n", 14), freetoken(token), NULL);
		lst->token = token;
		lst->previous = NULL;
		lst->next = NULL;
		lst->env = NULL;
		return (lst);
	}
	while (lst->next)
		lst = lst->next;
	lst->next = malloc(sizeof(t_lst));
	if (!lst->next)
		return (write(2, "Failed malloc\n", 14), freelst(lst), NULL);
	lst->next->previous = lst;
	lst->next->token = token;
	lst->next->next = NULL;
	lst->next->env = NULL;
	return (lst);
}

t_lst	*generate_lst(char *new, char *control, int beginning, int end)
{
	t_lst	*lst;
	t_token	*token;

	lst = NULL;
	while (new[end])
	{
		if (control[++end] == '0' && (new[end] == ' ' || ((new[end] == '<'
						|| new[end] == '>') && new[end - 1] != new[end])
				|| new[end] == '|' || new[end - 1] == '|'))
		{
			token = get_token(new, control, beginning, end);
			if (!token)
				return (freelst(lst), NULL);
			lst = lst_add(lst, token);
			if (!lst)
				return (NULL);
			beginning = end;
			while (new[beginning] && new[beginning] == ' ')
				beginning++;
			end = beginning;
		}
	}
	if (new[beginning])
		lst = lst_add(lst, get_token(new, control, beginning, end));
	return (lst);
}

t_lst	*split_lineofcmd(char *str, char *control, char **env, int status)
{
	char	*new;
	char	*new_control;
	t_lst	*lst;
	int		beginning;
	int		end;

	lst = NULL;
	beginning = 0;
	new = treat_dollar(str, control, env, status);
	if (!new)
		return (write(2, "Failed malloc\n", 14), NULL);
	new_control = deactivate_chars(new);
	if (!new_control)
		return (free(new), write(2, "Failed malloc\n", 14), NULL);
	while (new && new[beginning] && new[beginning] == ' ')
		beginning++;
	if (!new[beginning])
		return (free(new), free(new_control), NULL);
	end = beginning;
	lst = generate_lst(new, new_control, beginning, end);
	if (!lst)
		return (free(new), free(new_control), NULL);
	free(new);
	free(new_control);
	return (ft_lststart(lst));
}
