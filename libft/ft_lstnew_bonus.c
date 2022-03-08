/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mikuiper <mikuiper@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/29 13:35:32 by mikuiper      #+#    #+#                 */
/*   Updated: 2021/10/29 13:35:33 by mikuiper      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_elem;

	new_elem = malloc(sizeof(t_list) * 1);
	if (!(new_elem))
		return (NULL);
	new_elem->content = content;
	new_elem->next = NULL;
	return (new_elem);
}

/*
ft_lstnew(1) allocated memory for storing a new list element named 'new_elem'.
Next, the contents of 'new_elem' filled with user-specified variable 'content'.
Finally, the elements' variable 'next' is initialized as NULL.
*/