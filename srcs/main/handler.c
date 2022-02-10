/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:03:48 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/10 12:18:06 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal0(int keysym)
{
	if (keysym == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
	if (keysym == SIGINT)
	{
		g_signal = -1;
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "🤮 ", ft_strlen("🤮 "));
		rl_redisplay();
	}
}

void	signal1(int keysym)
{
	if (keysym == SIGINT)
	{
		write(1, "\n", 1);
		return ;
	}
	if (keysym == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		return ;
	}
	if (keysym == SIGSEGV)
	{
		write(2, "Segmentation fault (core dumped)\n", 33);
		return ;
	}
}

void	handler(int keysym)
{
	if (g_signal == 2)
		return ;
	if (g_signal == 0 || g_signal == -1)
		signal0(keysym);
	if (g_signal == 1)
		signal1(keysym);
}

void	signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGSEGV, handler);
}
