/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:16:02 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/04 19:49:32 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*my_exit(t_lst *lst, t_envlst *envlst, int act)
{
	int	ret;

	ret = 0;
	if (act)
	{
		if (lst->token->cmd[1] && lst->token->cmd[2])
			return (write(2, "exit : too many arguments\n", 26), NULL);
		if (!ft_strisdigit(lst->token->cmd[1]))
			return (write(2, "exit : numeric argument required\n", 33), NULL);
		if (lst->token->cmd[1])
			ret = ft_atoi(lst->token->cmd[1]);
		rl_clear_history();
		if (lst)
			freelst(lst);
		if (envlst)
			free_envlst(envlst, NULL);
		envlst = NULL;
		write(1, "exit\n", 5);
		exit(ret);
	}
	return (NULL);
}
