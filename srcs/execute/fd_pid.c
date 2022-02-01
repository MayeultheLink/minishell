/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_pid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:58:19 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/01 10:58:49 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*create_tab_fd(int n)
{
	int	*tab;
	int	i;

	tab = (int *)malloc(sizeof(int) * 2 * n);
	i = -1;
	while (++i < n)
	{
		if (pipe(tab + (i * 2)) == -1)
			return (NULL);
	}
	return (tab);
}

int	*create_tab_pid(int n)
{
	int	*tab;

	tab = (int *)malloc(sizeof(int) * (n));
	return (tab);
}

void	close_all_fd(int *tab_fd, int n)
{
	int	i;

	i = 0;
	while (i < (2 * n))
	{
		close(tab_fd[i]);
		i++;
	}
}

int	wait_all_pid(int *tab, int n)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < n - 1)
	{
		waitpid(tab[i], NULL, 0);
		i++;
	}
	waitpid(tab[i], &status, WEXITSTATUS(status));
	return (status);
}
