/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:09:11 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/01 18:38:34 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_plus(t_envlst *node, t_envlst *lst, char **split)
{
	node->name[ft_strlen(node->name) - 1] = 0;
	if (find_var(lst, node->name))
	{
		node->value = ft_strcatf((find_var(lst, node->name))->value,
				split[1], 2);
		if (!node->value)
			return (write(2, "Failed malloc\n", 14), 0);
	}
	free(node->env_str);
	node->env_str = NULL;
	node->env_str = ft_strcatf(node->name, "=", 0);
	if (!node->env_str)
		return (write(2, "Failed malloc\n", 14), 0);
	node->env_str = ft_strcatf(node->env_str, node->value, 1);
	if (!node->env_str)
		return (write(2, "Failed malloc\n", 14), 0);
	return (1);
}

t_envlst	*new_envnode(char *env, t_envlst *lst)
{
	t_envlst	*node;
	char		**split;

	if (!env || check_envname(env))
		return (NULL);
	node = (t_envlst *)malloc(sizeof(t_envlst));
	if (!node)
		return (write(2, "Failed malloc\n", 14), NULL);
	node->env_str = ft_strdup(env);
	split = ft_split_env(env);
	if (!node->env_str || !split[0] || !split[1])
		return (write(2, "Failed malloc\n", 14), NULL);
	node->name = split[0];
	node->value = split[1];
	if (split[0][ft_strlen(split[0]) - 1] == '+')
		if (!export_plus(node, lst, split))
			return (NULL);
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

	node = new_envnode(str, *lst);
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
