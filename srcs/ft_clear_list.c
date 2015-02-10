/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 13:10:39 by rbaum             #+#    #+#             */
/*   Updated: 2015/01/19 19:35:13 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void ft_list_clear(t_element *list)
{
	t_element *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp != NULL)
			free(tmp);
	}
	tmp = NULL;
}
