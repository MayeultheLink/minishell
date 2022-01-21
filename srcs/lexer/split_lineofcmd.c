/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lineofcmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 11:07:24 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/21 19:27:55 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*lst_add(t_lst *lst, t_token *token)
{
	t_lst	*tmp;

	tmp = lst;
	if (!lst)
	{
		lst = malloc(sizeof(t_lst));
		if (!lst)
			return (write(2, "Failed malloc\n", 14), freetoken(token), NULL);
		lst->token = token;
		lst->previous = NULL;
		lst->next = NULL;
		return (lst);
	}
	while (lst->next)
		lst = lst->next;
	lst->next = malloc(sizeof(t_lst));
	if (!lst->next)
		return (write(2, "Failed malloc\n", 14), freelst(tmp), NULL);
	lst->next->previous = lst;
	lst->next->token = token;
	lst->next->next = NULL;
	return (lst);
}

t_lst	*generate_lst(char *new, char *control, int beginning, int end)
{
	t_lst	*lst;
	t_token	*token;

	lst = NULL;
	while (new[++end])
	{
		if (control[end] == '0' && (new[end] == ' ' || ((new[end] == '<'
				|| new[end] == '>') && new[end - 1] != new[end])
				|| new[end] == '|' || new[end - 1] == '|'))
		{
			token = get_token(new, control, beginning, end);
			if (!token)
				return (freelst(ft_lststart(lst)), NULL);
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
	if (!lst)
		return (NULL);
	return (lst);
}

t_lst	*split_lineofcmd(char *str, char *control, char **env)
{
	char	*new;
	t_lst	*lst;
	int		beginning;
	int		end;

	lst = NULL;
	beginning = 0;
//	new = treat_dollar(str, control, env, 1);
	new = ft_strdup(str);
	if (!new)
		return (write(2, "Failed malloc\n", 14), NULL);
	while (new && new[beginning] && new[beginning] == ' ')
		beginning++;
	if (!new[beginning])
		return (free(new), NULL);
	end = beginning;
	lst = generate_lst(new, control, beginning, end);
	if (!lst)
		return (free(new), NULL);
	free(new);
	ft_lststart(lst)->env = ft_duptab(env);
	if (!ft_lststart(lst)->env)
		return (write(2, "Failed malloc\n", 14), freelst(lst), NULL);
	return (ft_lststart(lst));
}
