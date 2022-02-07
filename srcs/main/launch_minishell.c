/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:29:38 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/07 10:44:17 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_not_interactive(int ac, char **av, t_envlst *envlst)
{
	char	**env;
	t_lst	*lst;
	int		i;

	env = NULL;
	if (!ft_strncmp(av[1], "-c", 2))
	{
		i = 1;
		while (av[1][++i])
			if (av[1][i] != 'c')
				return (write(2, "invalid option for minishell\n", 29), 1);
		if (ac < 3)
			return (write(2, "-c: option requires an argument\n", 32), 1);
		env = make_envtab(env, envlst);
		lst = parse_lineofcmd(av[2], env, 0);
		if (lst)
			cmd_manager(lst, &env, &envlst);
		if (lst)
			freelst(lst);
		if (env)
			free(env);
		free_envlst(envlst, NULL);
		return (0);
	}
	return (write(2, "invalid option for minishell\n", 29), 1);
}

int	launch_interactive2(char *str, t_envlst *envlst, char ***env, int status)
{
	t_lst	*lst;
	size_t	i;

	add_history(str);
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (i == ft_strlen(str))
		return (free(str), 0);
	*env = make_envtab(*env, envlst);
	lst = parse_lineofcmd(str, *env, status);
	free(str);
	if (lst)
		status = cmd_manager(lst, env, &envlst);
	if (!lst || (lst->token && lst->token->path
			&& !(ft_lstend(lst)->token->path)))
		status = 127;
	if (lst)
		freelst(lst);
	return (status);
}

int	launch_interactive(t_envlst *envlst)
{
	char	**env;
	char	*str;
	int		status;

	g_signal = 0;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	status = 0;
	env = NULL;
	while (1)
	{
		if (!status)
			write(1, "🤤 ", ft_strlen("🤤 "));
		else
			write(1, "🤮 ", ft_strlen("🤮 "));
		str = readline("minishell> ");
		if (g_signal == -1)
			status = 130;
		g_signal = 0;
		if (!str)
			return (exit_minishell(str, env, envlst));
		if (ft_strlen(str) > 0)
			status = launch_interactive2(str, envlst, &env, status);
	}
	return (0);
}
