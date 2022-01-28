/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:39:20 by jpauline          #+#    #+#             */
/*   Updated: 2022/01/28 23:11:29 by mde-la-s         ###   ########.fr       */
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

void	free_envnode(t_envlst *node)
{
	free(node->name);
	free(node->value);
	free(node->env_str);
	free(node);
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

t_envlst	*free_envlst(t_envlst *lst, t_envlst *ret)
{
	if (lst->next)
		free_envlst(lst->next, ret);
	free_envnode(lst);
	return (ret);
}

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

void	write_export(t_envlst *lst, int fd)
{
	t_envlst	*node;

	node = lst;
	while (node)
	{
		if (ft_strcmp(node->name, "_"))
		{
			write(fd, "export ", 7);
			write(fd, node->name, ft_strlen(node->name));
			write(fd, "=\"", 2);
			write(fd, node->value, ft_strlen(node->value));
			write(fd, "\"\n", 2);
		}
		node = node->next;
	}
}

int	my_echo(char **cmd)
{
//	char	*str;
//	char	*control;
	int		n;
	int		i;

	n = 0;
	i = 1;
	if (cmd[1] && !ft_strncmp(cmd[1], "-n", 2))
	{
		while (cmd[1][i] && cmd[1][i] == 'n')
			i++;
		if (!cmd[1][i])
			n = 1;
	}
	if (n)
		i = 2;
	else
		i = 1;
	while (cmd[i])
	{
//		control = alloc_with(ft_strlen(cmd[i]), '0');
//		if (!control)
//			return (write(2, "Failed malloc\n", 14), 1);
//		str = treat_dollar(cmd[i], control, env, 0);
//		if (!str)
//			return (write(2, "Failed malloc\n", 14), 1);
		write(1, cmd[i], ft_strlen(cmd[i]));
//		free(control);
//		free(str);
		if (cmd[++i])
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
	return (0);
}

int	my_env(t_envlst *lst, int fd)
{
	t_envlst	*node;

	node = lst;
	while (node->next)
	{
		if ((node->value)[0] != '\0')
		{
			write(fd, node->env_str, ft_strlen(node->env_str));
			write(fd, "\n", 1);
		}
		node = node->next;
	}
	if (node->value[0] != '\0')
		write(fd, node->env_str, ft_strlen(node->env_str));
	write(fd, "\n", 1);
	return (0);
}

int	my_export(char **cmd, t_envlst **lst, int act, int fd)
{
	int	i;
	int	ret;

	if (!cmd[1])
	{
		write_export(*lst, fd);
		return (0);
	}
	i = 1;
	ret = 0;
	while (act && cmd[i])
	{
		if (set_env(lst, cmd[i]))
			ret = 1;
		i++;
	}
	i = 1;
	while (!act && cmd[i])
	{
		if (check_envname(cmd[i]))
			ret = 1;
		i++;
	}
	return (ret);
}

int	my_pwd(int fd)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (!buff)
	{
		write(2, "pwd : error\n", 12);
		return (1);
	}
	write(fd, buff, ft_strlen(buff));
	write(fd, "\n", 1);
	free(buff);
	return (0);
}

void	cd_error_message(char *str)
{
	write(2, "cd: ", 4);
	write(2, str, ft_strlen(str));
	write(2, ": No such file or directory\n", 28);
}

int	update_pwdlst(t_envlst **lst)
{
	t_envlst	*node_old;
	char		*path;
	char		*str;

	node_old = find_var(*lst, "PWD");
	str = ft_strcatf("OLDPWD=", node_old->value, 0);
	set_env(lst, str);
	free(str);
	path = getcwd(NULL, 0);
	if (!path)
		return (1);
	str = ft_strcatf("PWD=", path, 2);
	set_env(lst, str);
	free(str);
	return (0);
}

int	my_cd(char **cmd, t_envlst **lst, int act)
{
	char	*path;
	int		ret;

	if (!cmd[1] || cmd[2])
	{
		write(2, "cd: arguments error\n", 20);
		return (1);
	}
	path = getcwd(NULL, 0);
	if (!path)
	{
		write(2, "cd: getcwd error\n", 17);
		return (1);
	}
	path = ft_strcatf(path, "/", 1);
	path = ft_strcatf(path, cmd[1], 1);
	ret = chdir(path);
	if (ret)
		ret = chdir(cmd[1]);
	if (ret)
		cd_error_message(cmd[1]);
	free(path);
	if (!ret && act)
		ret = update_pwdlst(lst);
	return (ret);
}

int	my_unset(char **cmd, t_envlst **lst, int act)
{
	int			i;
	t_envlst	*node;

	if (!cmd[1])
		return (0);
	node = NULL;
	i = 1;
	while (act && cmd[i])
	{
		node = find_var(*lst, cmd[i]);
		if (node)
			*lst = del_envnode(*lst, node);
		i++;
	}
	return (0);
}
