/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:31:15 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/25 18:26:59 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*parse_lst(t_lst *lst, char **env)
{
	ft_lststart(lst)->env = ft_duptab(env);
	if (!ft_lststart(lst)->env)
		return (write(2, "Failed malloc\n", 14),
			freelst(ft_lststart(lst)), NULL);
	if (!error_pipe(ft_lststart(lst)) || !check_if_cmd(ft_lststart(lst))
		|| !get_cmd_with_arg(ft_lststart(lst)))
		return (freelst(ft_lststart(lst)), NULL);
	lst = check_redir(ft_lststart(lst));
	if (!lst)
		return (NULL);
	if (!del_pipes(ft_lststart(lst)))
		return (freelst(ft_lststart(lst)), NULL);
	return (ft_lststart(lst));
}
