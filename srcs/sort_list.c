/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 22:47:54 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/10 21:59:15 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    sort_list2(t_param *param)
{
    char        *tmp;

	if (param->bool[3] == 1 ?
		ft_strcmp(param->list->name, param->list->next->name) < 0 :
		ft_strcmp(param->list->name, param->list->next->name) > 0)
    {
        tmp = param->list->name;
        param->list->name = param->list->next->name;
        param->list->next->name = tmp;
        param->list = param->elem;
    }
    else
        param->list = param->list->next;
}

void    sort_list(t_param *param)
{
    param->list = param->elem;
    while (param->list->next != NULL)
        sort_list2(param);
}

void	sort_listime(t_param *param)
{
	char		*tmp;
	t_element	*list;
	t_element	*begin;

	begin = param->listime;
	list = param->listime;
	while (list->next != NULL)
	{
		if (param->bool[3] == 1 ?
			ft_strcmp(list->name, list->next->name) < 0 :
			ft_strcmp(list->name, list->next->name) > 0)
		{
			tmp = list->name;
			list->name = list->next->name;
			list->next->name = tmp;
			list = begin;
		}
		else
			list = list->next;
	}
}

void	sort_rec(t_param *param)
{
	char		*tmp;
	t_element	*list;

	list = param->rec;
	while (list->next != NULL)
	{
		if (param->bool[3] == 1 ?
			ft_strcmp(list->name, list->next->name) < 0 :
			ft_strcmp(list->name, list->next->name) > 0)
		{
			tmp = list->name;
			list->name = list->next->name;
			list->next->name = tmp;
			list = param->rec;
		}
		else
			list = list->next;
	}
}
