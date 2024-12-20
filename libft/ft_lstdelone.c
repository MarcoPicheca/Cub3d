/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marco <marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:35:19 by mapichec          #+#    #+#             */
/*   Updated: 2024/12/17 16:37:54 by marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	(*del)(lst->content);
	free(lst);
}

// lst : is the node to clear
// del : is the address of the function used to delete the content 

void	tkn_delone(t_token **current, t_token *del)
{
	(*current)->next = del->next;
	free(del->value);
	free(del);
}
