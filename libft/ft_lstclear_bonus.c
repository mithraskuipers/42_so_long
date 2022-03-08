/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/29 13:35:05 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/29 13:35:06 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next_element;

	if ((!(lst)) || (!(del)))
		return ;
	while (*lst)
	{
		next_element = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = next_element;
	}
}

/*
ft_lstclear(2) is similar to ft_lstdelone(). However, instead of deleting a 
single element of the linked list, all elements are deleted. This is done using 
a while loop, where as long as there is an element in the list, we iteratively 
call ft_lstdelone() to remove the current element. Prior to deletion, we store 
the location of the next element in a temporary variable 'next_element', which, 
after deletion of the current element, is set to be the new location of the 
current element.
*/