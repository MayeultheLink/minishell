/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:17:50 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/25 16:00:09 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_str_redir(char *str)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			while (str[i] && (str[i] == '<' || str[i] == '>'))
			{
				c++;
				i++;
			}
			while (str[i] && str[i] == ' ')
				i++;
			if (c > 2 || !str[i] || str[i] == '<' || str[i] == '>')
				return (0);
		}
		i++;
	}
	return (1);
}

int	error_redir(t_lst *lst)
{
	while (lst)
	{
		if (lst->token->type == REDIR)
			if (!check_str_redir(lst->token->str))
				return (write(2, "Syntax error : redirections\n", 28), 0);
		lst = lst->next;
	}
	return (1);
}
