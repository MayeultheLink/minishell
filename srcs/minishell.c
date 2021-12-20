/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:43:31 by mde-la-s          #+#    #+#             */
/*   Updated: 2021/12/20 17:16:25 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	print_split(char **split)
{
	int	i = 0;

	while (split && split[i])
	{
		printf("%d = %s", i, split[i]);
		printf("//\n");
		i++;
	}
}

void	parse_str(char *str)
{
	char *tmp;
	int	i = 0;
	int	j = 0;

	i = ft_strlen(str);
	while (j < ft_strlen(str))
	{
		if ((str[j] == '<' || str[j] == '>') && str[j + 1] == ' ')
			i--;
		j++;
	}
	j = 0;
	while (j < ft_strlen(str))
	{
		if (str[j] == '\'')
		{
			j++;
			while (str[j] != '\'')
				j++;
			j++;
		}
		if (str[j] == '$')
		{}
		j++;
	}
}*/

int	main(int ac, char **av, char **env)
{
	t_lst	*lst;
	char	*str;

	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		str = readline("minishell> ");
		if (ft_strlen(str) > 0)
		{
			add_history(str);
			if (!launch_cmd(str, env))
				break ;
			lst = split_minishell(str, str_control(str));
			while (lst)
			{
				printf("str = %s\n", lst->token->str);
				printf("type = %d\n", lst->token->type);
				lst = lst->next;
			}
			free(str);
		}
	}
	return (0);
}
