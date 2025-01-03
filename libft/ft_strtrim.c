/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:31:05 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/24 17:06:23 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*s;

	s = 0;
	if (s1 && set)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > i)
			j--;
		s = (char *)malloc(sizeof(char) * (j - i + 1));
		if (s)
			ft_strlcpy(s, &s1[i], j - i + 1);
	}
	return (s);
}

char	*ft_strtrim2(char *s1, char *set)
{
	size_t	i;
	size_t	j;
	char	*s;

	s = 0;
	if (s1 && set)
	{
		i = 0;
		j = ft_strlen(s1);
		while (s1[i] && ft_strchr(set, s1[i]))
			i++;
		while (s1[j - 1] && ft_strchr(set, s1[j - 1]) && j > i)
			j--;
		s = (char *)malloc(sizeof(char) * (j - i + 1));
		if (s)
			ft_strlcpy(s, &s1[i], j - i + 1);
	}
	if (s && s != NULL)
		free(s1);
	else
		return (NULL);
	return (s);
}
