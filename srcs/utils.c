/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:47:12 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/12 16:24:49 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_getenv(char *var, char **env)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(var, env[i], ft_strlen(var)))
		{
			result = malloc(sizeof(char) * (ft_strlen(env[i]) - ft_strlen(var)));
			if (!result)
				return (NULL);
			j = 0;
			while (env[i][j + ft_strlen(var) + 1])
			{
				result[j] = env[i][j + ft_strlen(var) + 1];
				j++;
			}
			result[j] = 0;
			return (result);
		}
		i++;
	}
	return (NULL);
}

t_lst	*ft_lststart(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->previous)
		lst = lst->previous;
	return (lst);
}

void	freelst(t_lst *lst)
{
	t_lst	*tmp;

	if (!lst)
		return ;
	while (lst->previous)
		lst = lst->previous;
	while (lst)
	{
		if (lst->token)
		{
			if (lst->token->str)
				free(lst->token->str);
			lst->token->str = NULL;
			if (lst->token->cmd)
				ft_freesplit(lst->token->cmd);
			if (lst->token->redir_in)
				free(lst->token->redir_in);
			lst->token->redir_in = NULL;
			if (lst->token->redir_out)
				free(lst->token->redir_out);
			lst->token->redir_out = NULL;
			free(lst->token);
			lst->token = NULL;
		}
		tmp = lst;
		lst = lst->next;
		free(tmp);
		tmp = NULL;
	}
}

char	*name_var(char *str)
{
	char	*name;
	int		i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (NULL);
	while (str[i] && str[i] != ' ' && str[i] != '"')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	name[i] = 0;
	while (--i >= 0)
		name[i] = str[i];
	return (name);
}

char	*treat_dollar(char *str, char *control, char **env)
{
	char	*new;
	char	*name;
	char	*tmp;
	int		i;
	int		j;
	int		c;

	c = ft_strlen(str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && control[i] == '0' && str[i + 1])
		{
			j++;
			name = name_var(&str[i + 1]);
			if (!name)
				return (NULL);
			tmp = my_getenv(name, env);
			if (!tmp)
			{
				free(name);
				return (NULL);
			}
			c += ft_strlen(tmp) - ft_strlen(name) - 1;
			free(name);
			free(tmp);
		}
		i++;
	}
	if (!j)
		return (ft_strdup(str));
	new = malloc(sizeof(char) * (c + 1));
	if (!new)
		return (NULL);
	new[c] = 0;
	i = 0;
	j = 0;
	while (str[j])
	{
		if (str[j] == '$' && control[j] == '0')
		{
			name = name_var(&str[j + 1]);
			if (!name)
			{
				free(new);
				return (NULL);
			}
			tmp = my_getenv(name, env);
			if (!tmp)
			{
				free(new);
				free(name);
				return (NULL);
			}
			c = 0;
			while (tmp[c])
				new[i++] = tmp[c++];
			j += ft_strlen(name) + 1;
			free(name);
			free(tmp);
		}
		if (str[j])
			new[i++] = str[j++];
	}
	return (new);
}
