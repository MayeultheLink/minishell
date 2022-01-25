/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:47:12 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/25 17:57:32 by mde-la-s         ###   ########.fr       */
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
				return (write(2, "Failed malloc\n", 14), NULL);
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
//	write(2, "Can't find env variable\n", 24);
	return (ft_strdup("/"));
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
	ft_freesplit(lst->env);
	while (lst)
	{
		if (lst->token)
		{
			if (lst->token->str)
				free(lst->token->str);
			lst->token->str = NULL;
			if (lst->token->path)
				free(lst->token->path);
			lst->token->path = NULL;
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

void	freetoken(t_token *token)
{
	if (token)
	{
		if (token->str)
			free(token->str);
		token->str = NULL;
		if (token->path)
			free(token->path);
		token->path = NULL;
		if (token->cmd)
			ft_freesplit(token->cmd);
		if (token->redir_in)
			free(token->redir_in);
		token->redir_in = NULL;
		if (token->redir_out)
			free(token->redir_out);
		token->redir_out = NULL;
		free(token);
		token = NULL;
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

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd") || !ft_strcmp(str, "pwd")
		|| !ft_strcmp(str, "export") || !ft_strcmp(str, "unset")
		|| !ft_strcmp(str, "env") || !ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

char	*treat_dollar(char *str, char *control, char **env, int trim)
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
		if (str[i] == '$')
			j++;
		i++;
	}
	if (!j)
		return (ft_strdup(str));
	i = 0;
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
	{
		tmp = ft_strtrim(str, " ");
		if (!tmp || !tmp[0])
		{
			free(tmp);
			tmp = NULL;
		}
		return (tmp);
	}
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
	if (trim)
	{
		tmp = ft_strtrim(new, " ");
		if (!tmp || !tmp[0])
		{
			free(tmp);
			tmp = NULL;
		}
		free(new);
		return (tmp);
	}
	return (new);
}
