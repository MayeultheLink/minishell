/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpauline <jpauline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:56:59 by jpauline          #+#    #+#             */
/*   Updated: 2021/10/19 17:10:44 by jpauline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*add_to_line(char **line, char add)
{
	char	*temp;
	int		index;

	index = 0;
	temp = malloc(sizeof(*temp) * (ft_strlen(*line) + 2));
	if (!temp)
	{
		free(*line);
		*line = NULL;
		return (NULL);
	}
	while ((*line)[index])
	{
		temp[index] = (*line)[index];
		index++;
	}
	temp[index++] = add;
	temp[index] = 0;
	free(*line);
	*line = temp;
	return (*line);
}

int	clean_return(int result, char **line)
{
	if (result == 0 && ft_strlen(*line) == 0)
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char	buff[2];
	char	*empty;
	int		index;
	int		result;

	if (!line)
		return (-1);
	*line = malloc(sizeof(**line) * 2);
	if (read(fd, buff, 0) == -1 || fd < 0 || !(*line))
		return (-1);
	empty = "";
	index = 0;
	(*line)[index] = empty[index];
	(*line)[1] = 0;
	result = read(fd, buff, 1);
	while (result > 0 && buff[0] != '\n')
	{
		buff[1] = 0;
		if (!add_to_line(line, buff[0]))
			return (-1);
		result = read(fd, buff, 1);
	}
	return (clean_return(result, line));
}
