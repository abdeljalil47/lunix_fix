/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdsebba <abdsebba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:17:29 by abdsebba          #+#    #+#             */
/*   Updated: 2024/11/11 03:01:32 by abdsebba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*content;
	void	*element;

	if (!lst || !f || !del)
		return (NULL);
	head = NULL;
	while (lst)
	{
		element = f(lst->content);
		content = ft_lstnew(element);
		if (!content)
		{
			del(element);
			ft_lstclear(&head, (*del));
			return (NULL);
		}
		ft_lstadd_back(&head, content);
		lst = lst->next;
	}
	return (head);
}
