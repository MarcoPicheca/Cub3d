/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 16:47:39 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/17 16:37:41 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	DESCRIPTION
    The  memchr()  function  scans  the  initial n bytes of the memory area
    pointed to by s for the first instance of c.  Both c and the  bytes  of
    the memory area pointed to by s are interpreted as unsigned char.

	RETURN VALUE
    The  memchr()  and memrchr() functions return a pointer to the matching
    byte or NULL if the character does not occur in the given memory area.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (str + i);
		i++;
	}
	return (NULL);
}
