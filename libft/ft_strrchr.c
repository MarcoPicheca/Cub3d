/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 18:28:30 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/17 16:35:50 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	The strrchr() function returns a pointer to the last occurrence of  the
    character c in the string s.

	The strchr() and strrchr() functions return a pointer  to  the  matched
    character  or NULL if the character is not found.  The terminating null
    byte is considered part of the string, so that if  c  is  specified  as
    '\0', these functions return a pointer to the terminator.
*/

char	*ft_strrchr(char *s, int c)
{
	char	*endptr;

	endptr = s + ft_strlen(s);
	while (endptr >= s)
	{
		if (*endptr == (char)c)
			return (endptr);
		endptr--;
	}
	if (!s)
		return (s);
	return (NULL);
}
