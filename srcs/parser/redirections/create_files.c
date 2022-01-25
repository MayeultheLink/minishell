/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:13:53 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/25 20:11:21 by mde-la-s         ###   ########.fr       */
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

void	redir_out(char *str)
{
	int		fd;
	char	*name;

	name = get_name(str);
	if (!name)
		return ;
	fd = open(name, O_WRONLY | O_CREAT, 0644);
	if (fd > -1)
		close(fd);
	else
		write(2, "Failure to create file\n", 23);
	free(name);
}

void	create_files(t_lst *lst)
{
	while (lst)
	{
		if (lst->token->type == REDIR)
		{
			if (lst->token->str[0] == '<' && lst->token->str[1] == '<')
				lst->token->fd_redir_in = heredoc(lst);
			else if (lst->token->str[0] == '>')
				redir_out(lst->token->str);
		}
		lst = lst->next;
	}
}
