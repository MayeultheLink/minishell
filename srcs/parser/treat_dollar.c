/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:22:24 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/07 18:33:27 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name_var(char *str)
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
		return (write(2, "Failed malloc\n", 14), NULL);
	while (--i >= 0)
		name[i] = str[i];
	return (name);
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
	char	*name;
	char	*tmp;
	char	*control;
	int		i;
	int		j;

	control = alloc_with(ft_strlen(new), '0');
	i = 0;
	j = 0;
	while (str_c[0][i])
	{
		if (str_c[0][i] == '$' && str_c[1][i] == '0')
		{
			name = name_var(&str_c[0][i + 1]);
			if (!name)
				return (free(new), NULL);
			tmp = my_getenv(name, env, status);
			if (!tmp)
				return (free(name), free(new), NULL);
			j = fill_new2(new, tmp, &control, j);
			i += ft_strlen(name) + 1;
			free(name);
		}
		if (str_c[0][i] && str_c[0][i] != '$')
		{
			new[j] = str_c[0][i];
			control[j++] = str_c[1][i++];
		}
	}
	return (control);
}

int	init_new(char *str, char *control, char **env, int status)
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
				return (-1);
			tmp = my_getenv(name, env, status);
			if (!tmp)
				return (free(name), -1);
			c += ft_strlen(tmp) - ft_strlen(name) - 1;
			free(tmp);
			free(name);
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
