/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:03:48 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/02/07 10:27:06 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int keysym)
{
	(void)keysym;
	if (g_signal == 2)
		return ;
	if (g_signal == 1)
		write(1, "\n", 1);
	else
	{
		g_signal = -1;
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "🤮 ", ft_strlen("🤮 "));
		rl_redisplay();
	}
}
