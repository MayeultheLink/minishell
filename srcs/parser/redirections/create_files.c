/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:13:53 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/31 18:39:37 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *str)
{
	char	*name;
	int		c;
	int		i;

	i = 0;
	while (str[i] == '<' || str[i] == '>')
		i++;
	c = 0;
	while (str[i + c])
		c++;
	name = alloc_with(c + 1, '0');
	if (!name)
		return (write(2, "Failed malloc\n", 14), NULL);
	name[0] = '/';
	c = 0;
	while (name[++c])
		name[c] = str[i++];
	name = ft_strcatf(getcwd(NULL, 0), name, 3);
	if (!name)
		return (write(2, "Failed malloc\n", 14), NULL);
	return (name);
}

int	redir_out(char *str)
{
	int		fd;
	char	*name;

	name = get_name(str);
	if (!name)
		return (0);
	fd = open(name, O_WRONLY | O_CREAT, 0644);
	if (fd > -1)
		close(fd);
	else
		return (write(2, "Failure to create file\n", 23), 0);
	free(name);
	return (1);
}

int	create_files(t_lst *lst, int status)
{
	while (lst)
	{
		if (lst->token->type == REDIR)
		{
			if (lst->token->str[0] == '<' && lst->token->str[1] == '<')
				lst->token->fd_redir_in = heredoc(lst, status);
			if (lst->token->str[0] == '>')
				if (!redir_out(lst->token->str))
					return (0);
		}
		lst = lst->next;
	}
	return (1);
}
