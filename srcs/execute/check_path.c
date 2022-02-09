/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:00:51 by jpauline          #+#    #+#             */
/*   Updated: 2022/02/09 12:19:37 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path(char *str)
{
	struct stat		st;
	int				ret;

	if (!str)
		return (0);
	ret = stat(str, &st);
	if (!ret && S_ISDIR(st.st_mode))
	{
		write(2, str, ft_strlen(str));
		write(2, ": is a directory\n", 17);
		return (1);
	}
	return (0);
}
