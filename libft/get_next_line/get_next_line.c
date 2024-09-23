/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrichaud <lrichaud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 23:14:42 by lrichaud          #+#    #+#             */
/*   Updated: 2024/01/25 21:57:30 by lrichaud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*reader(char *buffer, int fd);
char	*free_to_join(char	*s1, char	*s2);
char	*buffer_reorganizer(char *buffer);
char	*reader_core(char *line, char *buffer, ssize_t readed, int fd);

char	*get_next_line(int fd)
{
	static char	buffer[1025][BUFFER_SIZE + 1];
	char		*line;
	char		*line_resize;

	if (fd >= 1025 || fd == -1)
		return (NULL);
	if (read(fd, 0, 0) < 0)
		return (ft_bzero(buffer[fd], BUFFER_SIZE), NULL);
	line = reader(buffer[fd], fd);
	if (line == NULL)
		return (ft_bzero(buffer[fd], BUFFER_SIZE), NULL);
	buffer_reorganizer(buffer[fd]);
	line_resize = ft_strdup(line);
	free(line);
	return (line_resize);
}

char	*reader(char *buffer, int fd)
{
	ssize_t	readed;
	char	*line;
	int		i;

	i = 0;
	readed = 1;
	line = ft_strjoin(buffer, NULL);
	if (!line)
		return (ft_bzero(buffer, BUFFER_SIZE), NULL);
	buffer[BUFFER_SIZE] = '\0';
	line = reader_core(line, buffer, readed, fd);
	if (!line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
	{
		while (line[++i])
			line[i] = '\0';
	}
	return (line);
}

char	*buffer_reorganizer(char *buffer)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i + y] && i + y < BUFFER_SIZE)
	{
		buffer[y] = buffer[y + i];
		y++;
	}
	while (y < BUFFER_SIZE)
	{
		buffer[y] = '\0';
		y++;
	}
	return (buffer);
}

char	*free_to_join(char	*s1, char	*s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}

char	*reader_core(char *line, char *buffer, ssize_t readed, int fd)
{
	while (readed > 0 && !ft_strchr(buffer, '\n'))
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed < 0)
			return (free(line), NULL);
		if (readed == 0 && line[0] != '\0')
			return (line);
		else if (readed == 0)
			return (free(line), NULL);
		if (readed < BUFFER_SIZE)
		{
			while (readed <= BUFFER_SIZE)
				buffer[readed++] = '\0';
		}
		line = free_to_join(line, buffer);
		if (!line)
			return (NULL);
	}
	return (line);
}
