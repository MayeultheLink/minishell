/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <mde-la-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:04:02 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/24 16:10:03 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_cmd(t_lst *lst)
{
	while (lst)
	{
		if (lst->token->type == CMD)
			return (1);
		if (!lst->next)
		{
			write(2, "Error : no command\n", 19);
			return (0);
		}
		lst = lst->next;
	}
	return (1);
}

char	*get_path(char *cmd, char **split_path)
{
	char	*path;
	int	i;

	i = 0;
	while (split_path[i])
	{
		split_path[i] = ft_strcatf(split_path[i], "/", 1);
		if (!split_path[i])
			return (write(2, "Failed malloc\n", 14), NULL);
		split_path[i] = ft_strcatf(split_path[i], cmd, 1);
		if (!split_path[i])
			return (write(2, "Failed malloc\n", 14), NULL);
		if (!access(split_path[i], F_OK))
		{
			path = ft_strdup(split_path[i]);
			if (!path)
				return (write(2, "Failed malloc\n", 14), NULL);
			return (path);
		}
		i++;
	}
	write(2, "Command not found : ", 20);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (NULL);
}

char	*get_cmd_with_path(t_lst *lst)
{
	char	*str;
	char	**split_path;
	int	i;

	if (is_builtin(lst->token->str))
	{
		lst->token->builtin = 1;
		return (ft_strdup(lst->token->str));
	}
	if (!(access(lst->token->str, F_OK)))
		return(ft_strdup(lst->token->str));
	str = my_getenv("PATH");
	if (!str)
		return (write(2, "Failed malloc\n", 14), NULL);
	split_path = ft_split(str, ':');
	free(str);
	str = NULL;
	if (!split_path)
		return (write(2, "Failed malloc\n", 14), NULL);
	str = get_path(lst->token->str, split_path);
	ft_freesplit(split_path);
	if (!str)
		return (NULL);
	return (str);
}
