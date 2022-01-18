/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:45:58 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/17 12:33:13 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option(char **cmd)
{
	
}

void	echo(char **cmd)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "-n", 2))
			n = 1;
		i++;
	}
	i = 1;
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (!n)
			write(1, "\n", 1);
	}
}
