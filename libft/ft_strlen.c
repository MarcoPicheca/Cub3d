/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:29:19 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/17 16:36:27 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strlen_char(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == c)
		i++;
	return (i);
}

size_t	ft_strlen_2(const char *s, int flag)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (flag == 0)
	{
		while (s[i] != '\0')
			i++;
		return (i);
	}
	else if (flag == 1)
	{
		while (s[i] != '\n' && s[i])
			i++;
		return (i);
	}
	return (0);
}
