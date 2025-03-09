/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:30:36 by abdsebba          #+#    #+#             */
/*   Updated: 2024/10/28 23:54:52 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*move_node;
	t_list	*node;

	if (!lst || !del)
		return ;
	node = *lst;
	while (node)
	{
		move_node = node->next;
		ft_lstdelone(node, del);
		node = move_node;
	}
	*lst = NULL;
}
