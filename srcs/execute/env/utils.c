/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:39:20 by jpauline          #+#    #+#             */
/*   Updated: 2022/02/01 17:54:43 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_env(char *str)
{
	int		n;
	int		i;
	char	**tab;

	tab = (char **)malloc(sizeof (char *) * 2);
	if (tab == NULL)
		return (NULL);
	n = 0;
	while (str[n] && str[n] != '=')
		n++;
	tab[0] = (char *)malloc(sizeof (char) * (n + 1));
	if (tab[0] == NULL)
		return (NULL);
	i = -1;
	while (++i < n)
		tab[0][i] = str[i];
	tab[0][n] = '\0';
	if (str[n] == '=')
		tab[1] = ft_strdup(str + n + 1);
	else
		tab[1] = ft_strdup(str + n);
	return (tab);
}

int	is_envname(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_' && str[0] != '?')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[0]) && str[0] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	check_envname(char *str)
{
	char	**split;

	if (str[0] == '=')
	{
		write(2, "export: '", 9);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	split = ft_split_env(str);
	if (!is_envname(split[0]))
	{
		write(2, "export: '", 9);
		write(2, split[0], ft_strlen(split[0]));
		write(2, "': not a valid identifier\n", 26);
		free(split[0]);
		free(split[1]);
		free(split);
		return (1);
	}
	free(split[0]);
	free(split[1]);
	free(split);
	return (0);
}

int	envlst_len(t_envlst *lst)
{
	int			n;
	t_envlst	*node;

	if (!lst)
		return (0);
	n = 1;
	node = lst;
	while (node->next)
	{
		n++;
		node = node->next;
	}
	return (n);
}

t_envlst	*find_var(t_envlst *lst, char *var)
{
	t_envlst	*node;

	node = lst;
	while (node->next)
	{
		if (!ft_strcmp(node->name, var))
			return (node);
		node = node->next;
	}
	if (!ft_strcmp(node->name, var))
		return (node);
	return (NULL);
}
