/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rispay-s <rispay-s@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:20:15 by rispay-s          #+#    #+#             */
/*   Updated: 2024/12/06 15:12:07 by rispay-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

static int	ft_nl_check(char *save)
{
	int	i;

	if (!save)
		return (0);
	i = -1;
	while (save[++i] != '\0')
		if (save[i] == '\n')
			return (1);
	return (0);
}

static char	*ft_copy(char *save, char *buffer)
{
	char	*temp;

	temp = NULL;
	if (!save && buffer)
		return (ft_strdup(buffer));
	temp = ft_strjoin(save, buffer);
	ft_free(&save, 0);
	return (temp);
}

static char	*ft_before_nl(char *save)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!save)
		return (0);
	while (save[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (0);
	j = 0;
	while (j < i + 1)
	{
		line[j] = save[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_after_nl(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] != '\n')
		i++;
	if (save[i + 1] == '\0')
		return (ft_free(&save, 0));
	line = ft_substr(save, i + 1, ft_strlen(save));
	if (!line)
	{
		ft_free(&save, 0);
		return (NULL);
	}
	ft_free(&save, 0);
	return (line);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*save[4096];
	char		*line;
	long		count;

	line = NULL;
	count = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(&save[fd], 0));
	while (count > 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if ((count <= 0 && !save[fd]) || count == -1)
			return (ft_free(&save[fd], 0));
		buffer[count] = '\0';
		save[fd] = ft_copy(save[fd], buffer);
		if (ft_nl_check(save[fd]))
		{
			line = ft_before_nl(save[fd]);
			if (!line)
				return (ft_free(&save[fd], 0));
			return (save[fd] = ft_after_nl(save[fd]), line);
		}
	}
	return (ft_free(&save[fd], 1));
}
