/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:43:31 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/25 17:23:59 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(int ac, char **av, char **env)
{
	t_envlst	*envlst;
	char		**envtab;

	envlst = init_envlst(env);
	if (!envlst)
		return (write(2, "env list error\n", 15), 1);
	envlst = sort_envlst(envlst);
	envtab = NULL;
	if (ac >= 2)
		return (launch_not_interactive(ac, av, &envlst, &envtab));
	return (launch_interactive(&envlst, &envtab));
}
