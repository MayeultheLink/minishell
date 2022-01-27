/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:22:24 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/27 15:39:38 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name_var(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '"')
		i++;
	name = alloc_with(i, '0');
	if (!name)
		return (write(2, "Failed malloc\n", 14), NULL);
	while (--i >= 0)
		name[i] = str[i];
	return (name);
}

int	fill_new2(char *new, char *tmp, int j)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		new[j] = tmp[i];
		i++;
		j++;
	}
	free(tmp);
	return (j);
}

void	*fill_new(char *new, char *str, char *control, char **env)
{
	char	*name;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && control[i] == '0' && str[i + 1])
		{
			name = name_var(&str[i + 1]);
			if (!name)
				return (free(new), new = NULL);
			tmp = my_getenv(name, env);
			if (!tmp)
				return (free(name), free(new), new = NULL);
			j = fill_new2(new, tmp, j);
			i += ft_strlen(name) + 1;
			free(name);
		}
		if (str[i])
			new[j++] = str[i++];
	}
	return (NULL);
}

int	init_new(char *str, char *control, char **env)
{
	char	*name;
	char	*tmp;
	int		c;
	int		i;

	c = ft_strlen(str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && control[i] == '0' && str[i + 1])
		{
			name = name_var(&str[i + 1]);
			if (!name)
				return (0);
			tmp = my_getenv(name, env);
			if (!tmp)
				return (free(name), 0);
			c += ft_strlen(tmp) - ft_strlen(name) - 1;
			free(tmp);
			free(name);
		}
	}
	return (c);
}

char	*treat_dollar(char *str, char *control, char **env)
{
	char	*new;
	int		i;
	int		j;

	new = NULL;
	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] == '$')
			j++;
	if (!j)
		return (ft_strdup(str));
	i = init_new(str, control, env);
	if (i)
	{
		new = alloc_with(i, '0');
		if (!new)
			return (write(2, "Failed malloc\n", 14), NULL);
		fill_new(new, str, control, env);
		if (!new)
			return (NULL);
	}
	return (new);
}
