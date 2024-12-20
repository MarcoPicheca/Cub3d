/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:35:31 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/17 16:37:35 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
	The  memmove() function copies n bytes from memory area src to memory 
	area dest. The memory areas may overlap: copying takes place as though 
	the bytes in src are first copied into a temporary array that does not 
	overlap src or dest, and the bytes are then copied from the temporary 
	array to dest.
	
	RETURN VALUE
	The memmove() function returns a pointer to dest.
*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	i;

	i = (int)n;
	if (!dest && !src)
		return (0);
	if (dest > src)
		while (--i >= 0)
			((char *)dest)[i] = ((char *)src)[i];
	if (src > dest)
		ft_memcpy(dest, src, n);
	return ((void *)dest);
}
