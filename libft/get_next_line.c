/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-la-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 22:42:35 by mde-la-s          #+#    #+#             */
/*   Updated: 2022/01/27 16:13:20 by mde-la-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl(char **line, int i, int fd)
{
	char	buf;
	int		ret;

	ret = read(fd, &buf, 1);
	if (ret == 1 && buf != '\n')
	{
		ret = gnl(line, i + 1, fd);
		if (ret != -1)
			(*line)[i] = buf;
	}
	else if (ret != -1)
	{
		*line = (char *)malloc(sizeof(char) * (i + 1));
		if (*line != NULL)
			(*line)[i] = '\0';
		else
			ret = -1;
	}
	return (ret);
}

int	get_next_line(char **line)
{
	return (gnl(line, 0, 0));
}
