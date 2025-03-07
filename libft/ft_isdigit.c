/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:11:10 by mapichec          #+#    #+#             */
/*   Updated: 2025/01/07 15:03:24 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if ((c <= 57 && c >= 48))
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == 32 || c == '\t')
		return (1);
	return (0);
}
