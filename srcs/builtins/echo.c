/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:45:58 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/21 13:24:03 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **cmd)
{
	int	n;
	int	i;

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
		write(1, cmd[i], ft_strlen(cmd[i]));
		if (cmd[++i])
			write(1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
}
