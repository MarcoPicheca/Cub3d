/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:19:19 by mapichec          #+#    #+#             */
/*   Updated: 2025/01/18 17:31:30 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	i;
	size_t	k;
	size_t	j;
	char	*newstr;

	if (!s1 && !s2)
		return (NULL);
	else
	{
		i = 0;
		k = 0;
		j = 0;
		newstr = (char *)ft_calloc((ft_strlen_2(s1, 0)
					+ ft_strlen_2(s2, 0) + 1), 1);
		if (!newstr)
			return (NULL);
		while (s1[i])
			newstr[j++] = s1[i++];
		while (s2[k] != '\0')
			newstr[j++] = s2[k++];
		newstr[j++] = s2[k++];
		free(s1);
		return (newstr);
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char *buff, char *tmp)
{
	if (!buff)
		buff = ft_calloc(1, 1);
	if (!buff || !tmp || (!buff[0] && !tmp[0]))
	{
		free(tmp);
		free(buff);
		return (NULL);
	}
	return (ft_strjoin2(buff, tmp));
}
