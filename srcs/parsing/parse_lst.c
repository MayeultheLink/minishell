/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:31:15 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/07 11:28:01 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_lst(t_lst *lst)
{
	if (!error_pipe(ft_lststart(lst)) || !cmd(ft_lststart(lst))
		|| !check_redir(ft_lststart(lst)) || !del_pipes(ft_lststart(lst)))
		return (0);
	return (1);
}
