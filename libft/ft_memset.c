/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:35:04 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/17 16:37:32 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	DESCRIPTION
	The memset() function fills the first n bytes of the memory area pointed 
	to by s with the constant byte c.
	
	RETURN VALUE
	The memset() function returns a pointer to the memory area s.
*/

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = str;
	while (i < n)
		ptr[i++] = c;
	return ((void *)ptr);
}
