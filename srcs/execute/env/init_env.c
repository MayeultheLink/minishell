/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:06:30 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/01 11:08:02 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlst	*init_envlst(char **env)
{
	t_envlst	*lst;
	t_envlst	*node;
	int			i;

	lst = new_envnode(env[0]);
	if (!env[0] || !lst)
		return (NULL);
	node = lst;
	i = 1;
	while (env[i])
	{
		node->next = new_envnode(env[i]);
		if (!node->next)
			return (free_envlst(lst, NULL));
		node = node->next;
		i++;
	}
	return (lst);
}

t_envlst	*sort_envlst(t_envlst *lst)
{
	t_envlst	*sorted;
	t_envlst	*tmp;

	sorted = lst;
	lst = lst->next;
	sorted->next = NULL;
	while (lst->next)
	{
		tmp = lst;
		lst = lst->next;
		sorted = ins_envlst(tmp, sorted);
	}
	lst = ins_envlst(lst, sorted);
	return (lst);
}

char	**make_envtab(char **env, t_envlst *lst)
{
	int			i;
	int			n;
	t_envlst	*node;

	if (env)
		free(env);
	n = envlst_len(lst);
	if (!n)
		return (NULL);
	env = (char **)malloc(sizeof (char *) * (envlst_len(lst) + 1));
	if (!env)
		return (write(2, "envtab malloc error\n", 20), NULL);
	i = 0;
	node = lst;
	while (i < n)
	{
		env[i] = node->env_str;
		node = node->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
