/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:17:50 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/25 12:18:09 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_redir(t_lst *lst)
{
	int	i;
	int	b;
	int	c;

	while (lst)
	{
		c = 0;
		if (lst->token->type == REDIR)
		{
			i = 0;
			while (lst->token->str[i])
			{
				b = 0;
				if (lst->token->str[i] == '<' || lst->token->str[i] == '>')
				{
					c++;
					if (!lst->token->str[i + 1] || lst->token->str[i + 1] == ' ')
					{
						b = 1;
						i++;
					}
				}
				if (c > 2)
				{
					write(2, "Syntax error : redirections\n", ft_strlen("Syntax error : redirections\n"));
					return (0);
				}
				while (lst->token->str[i] && lst->token->str[i] == ' ')
					i++;
				if (b == 1 && (!lst->token->str[i]
						|| (lst->token->str[i] == '<' || lst->token->str[i] == '>')))
				{
					write(2, "Syntax error : redirections\n", ft_strlen("Syntax error : redirections\n"));
					return (0);
				}
				if (lst->token->str[i])
					i++;
			}
		}
		lst = lst->next;
	}
	return (1);
}
