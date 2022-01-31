/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:55:52 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/31 12:24:46 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_minishell(char *str, char **env, t_envlst *envlst)
{
	rl_clear_history();
	if (str)
		free(str);
	str = NULL;
	if (env)
		free(env);
	env = NULL;
	if (envlst)
		free_envlst(envlst, NULL);
	envlst = NULL;
	write(1, "exit\n", 5);
	return (0);
}
