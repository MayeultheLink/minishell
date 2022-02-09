/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lineofcmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:46:51 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/09 16:25:07 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*parse_lineofcmd(char *str, char **env, int status)
{
	t_lst	*lst;
	char	*control;
	size_t	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (i == ft_strlen(str))
		return (NULL);
	control = deactivate_chars(str);
	if (!control)
		return (NULL);
	lst = split_lineofcmd(str, &control, env, status);
	free(control);
	if (!lst)
		return (NULL);
	lst = parse_lst(lst, env, status);
	if (!lst)
		return (NULL);
	return (lst);
}
