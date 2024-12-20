/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:30:07 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/17 16:37:37 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    DESCRIPTION
        The  memcpy()  function  copies  n bytes from memory area src to memory
        area dest.  The memory areas must not overlap.  Use memmove(3)  if  the
        memory areas do overlap.

    RETURN VALUE
       The memcpy() function returns a pointer to dest.
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (!dest && !src)
		return (0);
	while (++i < n)
		((char *)dest)[i] = ((char *)src)[i];
	return (dest);
}
