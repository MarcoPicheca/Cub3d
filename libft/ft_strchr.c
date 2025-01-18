/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:16:25 by mapichec          #+#    #+#             */
/*   Updated: 2025/01/18 17:49:00 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	The  strchr() function returns a pointer to the first occurrence of the
    character c in the string s.

	The strchr() and strrchr() functions return a pointer  to  the  matched
    character  or NULL if the character is not found.  The terminating null
    byte is considered part of the string, so that if  c  is  specified  as
    '\0', these functions return a pointer to the terminator.
*/

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	if (!s)
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

int	ft_strchr_2(char *s, int c)
{
	int		i;

	i = 0;
	if (c == 0)
		return (0);
	while (s[i] && s[i] != '\0' && s[i] != (unsigned char)c)
		i++;
	if (s[i] != (unsigned char)c)
		return (0);
	return (1);
}
