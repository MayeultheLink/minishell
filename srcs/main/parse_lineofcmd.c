/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lineofcmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:46:51 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/27 13:01:00 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*parse_lineofcmd(char *str, char **env)
{
	t_lst	*lst;
	char	*control;

	control = deactivate_chars(str);
	if (!control)
		return (NULL);
	lst = split_lineofcmd(str, control, env);
	if (!lst)
		return (free(control), NULL);
	lst = parse_lst(lst, env);
	if (!lst)
		return (free(control), NULL);
	free(control);
	return (lst);
}
