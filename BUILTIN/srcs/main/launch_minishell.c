/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:29:38 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/28 20:02:12 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_not_interactive(int ac, char **av, t_envlst **envlst, char ***env)
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
		*env = make_envtab(*env, *envlst);
		lst = parse_lineofcmd(av[2], *env);
		if (lst)
			cmd_manager(lst, *env, envlst);
		if (lst)
			freelst(lst);
		if (*env)
			free(*env);
		free_envlst(*envlst, NULL);
		return (0);
	}
	return (write(2, "invalid option for minishell\n", 29), 1);
}

int	launch_interactive(t_envlst **envlst, char ***env)
{
	t_lst	*lst;
	char	*str;
	int		status;

	g_signal = 0;
	status = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = ft_itoa(status);
		set_env(envlst, ft_strcatf("?=", str, 0));
		write(1, str, ft_strlen(str));
		free(str);
		str = readline(" minishell> ");
		if (!str)
			return (exit_minishell(str));
		if (ft_strlen(str) > 0)
		{
			if (!ft_strcmp(str, "exit"))
				return (exit_minishell(str));
			add_history(str);
			*env = make_envtab(*env, *envlst);
			lst = parse_lineofcmd(str, *env);
			if (lst)
				status = cmd_manager(lst, *env, envlst);
			else
				status = 1;
			if (lst)
				freelst(lst);
		}
		free(str);
	}
	if (*env)
		free(*env);
	free_envlst(*envlst, NULL);
	return (0);
}
