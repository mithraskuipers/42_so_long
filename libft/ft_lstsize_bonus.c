/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/29 13:35:41 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/29 13:35:42 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

/*
While the linked list 'lst' has not reached its end, I keep jumping to the
next element in the list. While doing this, I keep track of a counter var 'i', 
that informs me how many elements there inside 'lst'
*/
