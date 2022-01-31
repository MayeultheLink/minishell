/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:43:31 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/31 11:34:01 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	main(int ac, char **av, char **env)
{
	t_envlst	*envlst;
	char		*shlvl;

	envlst = init_envlst(env);
	if (!envlst)
		return (1);
	envlst = sort_envlst(envlst);
	shlvl = ft_strcatf("SHLVL=", ft_itoa(ft_atoi((find_var(envlst,
							"SHLVL"))->value) + 1), 2);
	if (set_env(&envlst, shlvl))
		return (free(shlvl), 1);
	free(shlvl);
	if (ac >= 2)
		return (launch_not_interactive(ac, av, envlst));
	return (launch_interactive(envlst));
}
