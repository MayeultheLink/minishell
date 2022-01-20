/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:43:31 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/20 21:46:13 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_g;

void	handler()
{
	if (g_g == 2)
		return ;
	if (g_g == 1)
		write(1, "\n", 1);
	else
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	t_lst	*lst;
	char	*str;
	int		i;

	g_g = 0;
	if (ac >= 2)
	{
		if (!ft_strncmp(av[1], "-c", 2))
		{
			i = 1;
			while (av[1][++i])
			{
				if (av[1][i] != 'c')
				{
					write(2, "invalid option for minishell\n", 29);
					return (1);
				}
			}
			if (ac < 3)
			{
				write(2, "minishell: -c: option requires an argument\n", 43);
				return (1);
			}
			lst = split_minishell(av[2], str_control(av[2]), env);
			lst = parse_lst(lst);
			if (lst)
				cmd_manager(lst, env);
			if (lst)
				freelst(lst);
			return (0);
		}
		else
		{
			write(2, "invalid option for minishell\n", 29);
			return (1);
		}
	}
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("minishell> ");
		if (!str)
		{
			free(str);
			rl_clear_history();
			write(1, "exit\n", 5);
			return (0);
		}
		if (ft_strlen(str) > 0)
		{
			if (!ft_strcmp(str, "exit"))
			{
				free(str);
				str = NULL;
				rl_clear_history();
				write(1, "exit\n", 5);
				return (0);
			}
			add_history(str);
			lst = split_minishell(str, str_control(str), env);
			lst = parse_lst(lst);
			if (lst)
				cmd_manager(lst, env);
			if (lst)
				freelst(lst);
		}
		free(str);
	}
	return (0);
}

/*			int j = 0;
			int	i;
			lst = parse_lst(lst);
			while (lst)
			{
				i = 0;
				j++;
				printf("Cellule %d :\n", j);
				printf("str = %s\n", lst->token->str);
				while (lst && lst->token && lst->token->cmd && lst->token->cmd[i])
				{
					printf("cmd[%d] = %s\n", i, lst->token->cmd[i]);
					i++;
				}
				if (lst->token->redir_in)
					printf("redirection in = %s\n", lst->token->redir_in);
				if (lst->token->type_redir_in == 1)
					printf("redirection in append\n");
				if (lst->token->redir_out)
					printf("redirection out = %s\n", lst->token->redir_out);
				if (lst->token->type_redir_out == 1)
					printf("redirection out append\n");
				if (!lst->next)
					break ;
				lst = lst->next;
			}
			lst = ft_lststart(lst);*/
