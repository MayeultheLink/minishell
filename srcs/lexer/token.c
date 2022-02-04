/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 19:02:02 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/04 14:48:41 by mde-la-s         ###   ########.fr       */
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

t_token	*set_all_to_null(t_token *token)
{
	token->str = NULL;
	token->path = NULL;
	token->cmd = NULL;
	token->redir_in = NULL;
	token->redir_out = NULL;
	token->builtin = 0;
	token->type_redir_in = -1;
	token->type_redir_out = -1;
	token->fd_redir_in = -2;
	token->type = -1;
	return (token);
}

t_token	*init_token(char *str, char *control, int beg, int end)
{
	t_token	*token;
	int		c;
	int		i;

	token = malloc(sizeof(t_token));
	if (!token)
		return (write(2, "Failed malloc\n", 14), NULL);
	token = set_all_to_null(token);
	c = 0;
	i = -1;
	while (beg + ++i < end)
		if ((str[beg + i] == '"' || str[beg + i] == '\'')
			&& control[beg + i] == '0')
			c++;
	if (c == (int)ft_strlen(str))
		return (free(token), NULL);
	token->str = alloc_with((end - beg - c), '0');
	if (!token->str)
		return (write(2, "Failed malloc\n", 14), free(token), NULL);
	return (token);
}

t_token	*get_token(char *str, char *control, int beg, int end)
{
	t_token	*token;
	int		i;
	int		c;

	token = init_token(str, control, beg, end);
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
	token->type = get_type(token, control[beg + i]);
	return (token);
}
