/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:14:04 by zelhajou          #+#    #+#             */
/*   Updated: 2023/05/31 22:29:26 by zelhajou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *read_line(int fd, char *buffer, char *saved);
static char *extract_line(char **saved);

char *get_next_line(int fd)
{
	static char *saved = NULL;
	char *buffer;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);

	if (!saved)
		saved = ft_strdup("");

	saved = read_line(fd, buffer, saved);
	if (!saved)
		return (NULL);
	line = extract_line(&saved);

	return (line);
}

char *read_line(int fd, char *buffer, char *saved)
{
	int bytes_read;
	char *temp;
	char *newline_ptr;

	bytes_read = 1;
	newline_ptr = ft_strchr(saved, '\n');

	while (newline_ptr == NULL && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break;
		buffer[bytes_read] = '\0';
		temp = saved;
		saved = ft_strjoin(saved, buffer);
		free(temp);
		newline_ptr = ft_strchr(saved, '\n');
	}
	free(buffer);
	if (bytes_read < 0)
	{
		free(saved);
		return (NULL);
	}
	return (saved);
}

static char *extract_line(char **saved)
{
	char *line;
	char *temp;
	int i;

	i = 0;
	while ((*saved)[i] != '\n' && (*saved)[i] != '\0')
		i++;

	return (line);
}