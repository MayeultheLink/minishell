/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:43:31 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/10 17:25:10 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\nminishell> ", 12);
	else
		write(1, "\b\b  \b\b", 6);
}

int	main(int ac, char **av, char **env)
{
	t_lst	*lst;
	char	*str;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	if (ac >= 2 && !ft_strncmp(av[1], "-c", 2))
	{
		if (ac < 3)
		{
			write(2, "minishell: -c: option requires an argument\n", 43);
			return (1);
		}
		lst = split_minishell(av[2], str_control(av[2]));
		if (parse_lst(lst))
			cmd_manager(lst, env);
		freelst(lst);
		return (0);
	}
	while (1)
	{
		str = readline("minishell> ");
		if (!str)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		if (ft_strlen(str) > 0)
		{
			add_history(str);
			if (!ft_strncmp(str, "exit", 4))
			{
				free(str);
				rl_clear_history();
				write(1, "exit\n", 5);
				return (0);
			}
			lst = split_minishell(str, str_control(str));
			if (lst && parse_lst(lst))
				cmd_manager(lst, env);
			freelst(lst);
			free(str);
		}
	}
	return (0);
}

/*			j = 0;
			int	i;
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
