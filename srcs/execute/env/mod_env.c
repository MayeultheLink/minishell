/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:09:11 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/01 11:12:28 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlst	*new_envnode(char *env)
{
	t_envlst	*node;
	char		**split;

	if (!env)
		return (NULL);
	if (check_envname(env))
		return (NULL);
	node = NULL;
	node = (t_envlst *)malloc(sizeof(t_envlst));
	if (!node)
		return (write(2, "Failed malloc\n", 14), NULL);
	node->env_str = ft_strdup(env);
	split = ft_split_env(env);
	if (!node->env_str || !split[0] || !split[1])
		return (write(2, "Failed malloc\n", 14), NULL);
	node->name = split[0];
	node->value = split[1];
	node->next = NULL;
	free(split);
	return (node);
}

t_envlst	*ins_envlst(t_envlst *node, t_envlst *sorted)
{
	t_envlst	*tmp;

	if (ft_strcmp(node->name, sorted->name) < 0)
	{
		node->next = sorted;
		sorted = node;
		return (sorted);
	}
	tmp = sorted;
	while (tmp->next)
	{
		if (ft_strcmp(node->name, tmp->next->name) < 0)
		{
			node->next = tmp->next;
			tmp->next = node;
			return (sorted);
		}
		tmp = tmp->next;
	}
	tmp->next = node;
	node->next = NULL;
	return (sorted);
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

t_envlst	*del_envnode(t_envlst *lst, t_envlst *node)
{
	t_envlst	*tmp;

	if (!node || !lst)
		return (lst);
	if (node == lst)
	{	
		lst = node->next;
		free_envnode(node);
		return (lst);
	}
	tmp = lst;
	while (tmp->next)
	{
		if (tmp->next == node)
		{
			tmp->next = node->next;
			free_envnode(node);
			return (lst);
		}
		tmp = tmp->next;
	}
	return (lst);
}

int	set_env(t_envlst **lst, char *str)
{
	t_envlst	*node;
	t_envlst	*old;

	node = new_envnode(str);
	if (!node)
		return (1);
	old = find_var(*lst, node->name);
	if (old && node->value[0])
		*lst = del_envnode(*lst, old);
	if (old && !node->value[0])
	{
		free_envnode(node);
		return (0);
	}
	*lst = ins_envlst(node, *lst);
	return (0);
}
