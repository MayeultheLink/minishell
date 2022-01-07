/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:43:31 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/07 18:26:00 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_lst	*lst;
	char	*str;

	(void)ac;
	(void)av;
	(void)env;
	int	i;
	i = 0;
	int	j;
	lst = NULL;
	str = NULL;
	while (1)
	{
		str = readline("minishell> ");
		if (ft_strlen(str) > 0)
		{
			add_history(str);
			if (!ft_strcmp(str, "exit"))
			{
				free(str);
				rl_clear_history();
				return (0);
			}
			lst = split_minishell(str, str_control(str));
			j = 0;
/*			while (lst)
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
			}*/
			if (lst)
			{
				cmd_manager(lst, env);
				freelst(lst);
			}
			free(str);
		}
	}
	free(str);
	rl_clear_history();
	return (0);
}
