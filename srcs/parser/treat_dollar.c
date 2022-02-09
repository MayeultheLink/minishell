/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:22:24 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/09 16:26:31 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_name_tmp(char **tmp, char *str, char **env, int status)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i == 0 && str[0] == '?')
		i++;
	name = alloc_with(i, '0');
	if (!name)
		return (write(2, "Failed malloc\n", 14), -1);
	while (--i >= 0)
		name[i] = str[i];
	*tmp = my_getenv(name, env, status);
	if (!*tmp)
		return (free(name), -1);
	i = ft_strlen(name) + 1;
	free(name);
	return (i);
}

int	fill_new2(char *new, char *tmp, char **control, int j)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		new[j] = tmp[i];
		if (tmp[i] != ' ')
			(*control)[j] = '1';
		i++;
		j++;
	}
	free(tmp);
	return (j);
}

char	*fill_new(char *new, char **str_c, char **env, int status)
{
	char	*tmp;
	char	*control;
	int		i;
	int		j[2];

	control = alloc_with(ft_strlen(new), '0');
	i = 0;
	j[0] = 0;
	while (str_c[0][i])
	{
		if (str_c[0][i] == '$' && str_c[1][i] == '0')
		{
			j[1] = set_name_tmp(&tmp, &str_c[0][i + 1], env, status);
			if (j[1] == -1)
				return (free(control), NULL);
			i += j[1];
			j[0] = fill_new2(new, tmp, &control, j[0]);
		}
		if (str_c[0][i] && str_c[0][i] != '$')
		{
			new[j[0]] = str_c[0][i];
			control[j[0]++] = str_c[1][i++];
		}
	}
	return (control);
}

int	init_new(char *str, char *control, char **env, int status)
{
	char	*tmp;
	int		c;
	int		i;
	int		set;

	c = ft_strlen(str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && control[i] == '0' && str[i + 1])
		{
			set = set_name_tmp(&tmp, &str[i + 1], env, status);
			c += ft_strlen(tmp) - set;
			free(tmp);
		}
	}
	return (c);
}

char	*treat_dollar(char **new, char **str_c, char **env, int status)
{
	char	*control;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (str_c[0][++i])
		if (str_c[0][i] == '$' && str_c[1][i] == '0')
			j++;
	if (!j)
		return (*new = ft_strdup(str_c[0]), ft_strdup(str_c[1]));
	else
	{
		i = init_new(str_c[0], str_c[1], env, status);
		*new = alloc_with(i, '0');
		if (!*new)
			return (write(2, "Failed malloc\n", 14), NULL);
		control = fill_new(*new, str_c, env, status);
		return (control);
	}
}
