/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishirais <ishirais@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:35:40 by ishirais          #+#    #+#             */
/*   Updated: 2020/10/22 13:07:56 by ishirais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*line_n_str(char *line)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i] != '\n')
		i++;
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (*line != '\n')
		*str++ = *line++;
	*str = '\0';
	free(line - i);
	return (str - i);
}

int		process_save(int ret, char **line, char **save)
{
	char	*tmp;

	*line = ft_strdup(*save);
	free(*save);
	*save = NULL;
	if (ft_strchr(*line, '\n'))
	{
		tmp = ft_strchr(*line, '\n') + 1;
		*save = ft_strdup(tmp);
		tmp = line_n_str(*line);
		*line = ft_strdup(tmp);
		free(tmp);
		ret = 1;
	}
	return (ret);
}

void	line_check(char **line, int ret, char *buf)
{
	char	*tmp;

	buf[ret] = '\0';
	if (!*line)
		*line = ft_strdup(buf);
	else
	{
		tmp = ft_strjoin(*line, buf);
		free(*line);
		*line = ft_strdup(tmp);
		free(tmp);
	}
}

int		process_read(int fd, char **line, char **save, char *buf)
{
	int		ret;
	char	*tmp;

	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		line_check(line, ret, buf);
		if (*line[0] == '\n')
		{
			tmp = &(*line)[1];
			*save = ft_strdup(tmp);
			free(*line);
			*line = ft_strdup("");
			break ;
		}
		else if (ft_strchr(*line, '\n'))
		{
			tmp = ft_strchr(*line, '\n') + 1;
			*save = ft_strdup(tmp);
			tmp = line_n_str(*line);
			*line = ft_strdup(tmp);
			free(tmp);
			break ;
		}
	}
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	char		*buf;
	static char	*save;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	*line = NULL;
	ret = 0;
	buf[BUFFER_SIZE] = '\0';
	if (save)
		ret = process_save(ret, line, &save);
	if (!ret)
		ret = process_read(fd, line, &save, buf);
	if (!*line)
		*line = ft_strdup("");
	free(buf);
	if (ret > 0)
		ret = 1;
	return (ret);
}
