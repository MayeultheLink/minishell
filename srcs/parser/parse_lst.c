/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:31:15 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/09 16:57:53 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*parse_lst(t_lst *lst, char **env, int status)
{
	ft_lststart(lst)->env = ft_duptab(env);
	if (!ft_lststart(lst)->env)
		return (write(2, "Failed malloc\n", 14),
			freelst(lst), NULL);
	if (!error_pipe(ft_lststart(lst)))
		return (freelst(lst), NULL);
	while (lst->token->type == REDIR)
	{
		if (lst->next && lst->next->token->type == REDIR)
			lst = lst->next;
		else if (!lst->next)
			return (create_files(ft_lststart(lst), status), ft_lststart(lst));
		else
			break ;
	}
	if (!get_cmd_with_arg(ft_lststart(lst)))
		return (freelst(lst), NULL);
	lst = check_redir(ft_lststart(lst), status);
	if (!lst)
		return (NULL);
	lst = del_pipes(ft_lststart(lst));
	return (ft_lststart(lst));
}
