/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/29 13:34:52 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/29 13:34:55 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*final_element;

	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	final_element = ft_lstlast(*lst);
	final_element->next = new;
}

/*
ft_lstadd_back(2) first checks whether there is no element at the start of the
double pointer lst. If that is the case, it fills in the spot with the pointer 
of the element 'new'. Otherwise, it reads out the last element of the linked 
list using ft_lstlast(1), and points that element to 'new'.
*/