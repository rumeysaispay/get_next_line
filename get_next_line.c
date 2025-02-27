/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rispay-s <rispay-s@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:58:18 by rispay-s          #+#    #+#             */
/*   Updated: 2024/12/06 15:17:35 by rispay-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

static int	ft_nl_check(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static char	*ft_copy(char *buffer, char *save)
{
	if (!save)
		return (ft_strdup(buffer));
	else
		return (ft_strjoin(save, buffer));
	return (NULL);
}

static char	*ft_before_nl(char *save)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = ft_nl_check(save);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_after_nl(char *save)
{
	char	*temp;
	int		len;
	int		k;

	k = 0;
	len = ft_nl_check(save);
	if (!len || !save[len])
		return (free(save), save = NULL, NULL);
	temp = malloc(sizeof(char) * ((ft_strlen(save) - len) + 1));
	if (!temp)
		return (NULL);
	while (save[len + k])
	{
		temp[k] = save[len + k];
		k++;
	}
	temp[k] = '\0';
	free(save);
	save = NULL;
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*save = NULL;
	char		*line;
	int			count;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || !buffer)
		return (free(buffer), buffer = NULL, NULL);
	count = 1;
	while (count > 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if ((count <= 0 && !save) || count == -1)
			return (free(buffer), buffer = NULL, NULL);
		buffer[count] = '\0';
		save = ft_copy(buffer, save);
		if (!save)
			return (free(buffer), buffer = NULL, NULL);
		if (ft_nl_check(save))
		{
			line = ft_before_nl(save);
			return (save = ft_after_nl(save), free(buffer), line);
		}
	}
	return (free(buffer), buffer = NULL, ft_free(&save));
}
