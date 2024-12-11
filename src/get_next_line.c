/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapichec <mapichec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:58:24 by adapassa          #+#    #+#             */
/*   Updated: 2024/12/11 19:01:52 by mapichec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	rd_check(int i, char *buff, char *tmp)
{
	if (i < 0)
	{
		free(tmp);
		free(buff);
		return (0);
	}
	return (1);
}

static char	*ft_strchr2(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	if (!str)
		return (NULL);
	if (c == 0)
		return (str + ft_strlen(s));
	while (s[i] != (unsigned char)c)
	{
		if (!str[i])
			break ;
		else
			i++;
	}
	if (str[i] != (unsigned char)c)
		return (NULL);
	return ((str + i));
}

static char	*ft_read(char *buff, int fd)
{
	int		i;
	char	*tmp;

	tmp = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 1;
	while (!ft_strchr2(buff, '\n') && i != 0)
	{
		i = read(fd, tmp, BUFFER_SIZE);
		if (rd_check(i, buff, tmp) == 0)
			return (NULL);
		tmp[i] = 0;
		buff = ft_strjoin_gnl(buff, tmp);
		if (!buff)
		{
			free(buff);
			return (NULL);
		}
	}
	free(tmp);
	return (buff);
}

static char	*next_line(char *buff)
{
	int		i;
	int		j;
	char	*tmp;

	i = ft_strlen_2(buff, 1);
	tmp = (char *)ft_calloc(i + 2, sizeof(char));
	if (!tmp)
	{
		free(buff);
		return (NULL);
	}
	j = 0;
	while (buff[j] != '\n' && buff[j] != '\0' && j < i)
	{
		tmp[j] = buff[j];
		j++;
	}
	if (buff[j] == '\n')
		tmp[j++] = '\n';
	return (tmp);
}

static char	*cut_line(char *buff)
{
	char	*new;
	int		i;
	int		j;
	int		z;

	i = ft_strlen_2(buff, 0);
	j = ft_strlen_2(buff, 1);
	new = (char *)ft_calloc(i - j + 1, sizeof(char));
	if (!new)
	{
		free(buff);
		return (NULL);
	}
	j++;
	z = 0;
	while (j < i && buff[j] != '\0')
		new[z++] = buff[j++];
	free(buff);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buff = ft_read(buff, fd);
	if (!buff)
		return (NULL);
	line = next_line(buff);
	buff = cut_line(buff);
	if (!buff || !line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
