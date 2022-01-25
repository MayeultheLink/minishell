/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:29:38 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/21 17:49:41 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_not_interactive(int ac, char **av, char **env)
{
	t_lst	*lst;
	int		i;

	if (!ft_strncmp(av[1], "-c", 2))
	{
		i = 1;
		while (av[1][++i])
		{
			if (av[1][i] != 'c')
				return (write(2, "invalid option for minishell\n", 29), 1);
		}
		if (ac < 3)
			return (write(2, "-c: option requires an argument\n", 32), 1);
		lst = parse_lineofcmd(av[2], env);
		if (lst)
			cmd_manager(lst, env);
		if (lst)
			freelst(lst);
		return (0);
	}
	return (write(2, "invalid option for minishell\n", 29), 1);
}

int	launch_interactive(char **env)
{
	t_lst	*lst;
	char	*str;

	g_signal = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("minishell> ");
		if (!str)
			return (exit_minishell(str));
		if (ft_strlen(str) > 0)
		{
			if (!ft_strcmp(str, "exit"))
				return (exit_minishell(str));
			add_history(str);
			lst = parse_lineofcmd(str, env);
			if (lst)
				cmd_manager(lst, env);
			if (lst)
				freelst(lst);
		}
		free(str);
	}
	return (0);
}
