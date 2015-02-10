/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_t.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 16:17:59 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/10 22:13:21 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	sort_list_swap(t_param *param, t_element *begin, t_element *begin2)
{
	char *tmp;

	tmp = param->list->name;
	param->list->name = param->list->next->name;
	param->list->next->name = tmp;
	param->list = begin;
	tmp = param->listime->name;
	param->listime->name = param->listime->next->name;
	param->listime->next->name = tmp;
	param->listime = begin2;
}

void	sort_equ(t_param *param)
{
	sort_list(param);
	sort_listime(param);
}

void	ft_next(t_param *param)
{
	param->list = param->list->next;
	param->listime = param->listime->next;
}

void	sort_list_time(t_param *param)
{
	struct stat		*one;
	struct stat		*two;
	t_element		*begin;
	t_element		*begin2;

	one = (struct stat*)malloc(sizeof(struct stat));
	two = (struct stat*)malloc(sizeof(struct stat));
	param->list = param->elem;
	begin = param->elem;
	begin2 = param->listime;
	while (param->list->next != NULL)
	{
		if (lstat(param->listime->name, one) == -1)
			perror("stat");
		if (lstat(param->listime->next->name, two) == -1)
			perror("stat");
		if (param->bool[3] == 0 ? one->st_mtime < two->st_mtime :
			one->st_mtime > two->st_mtime)
			sort_list_swap(param, begin, begin2);
//		else if (one->st_mtime == two->st_mtime)
		//		sort_equ(param);
		else
			ft_next(param);
	}
}
