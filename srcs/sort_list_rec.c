/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_rec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 11:31:44 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/09 15:07:46 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_option_rec(t_param *param)
{
	sort_rec(param);
	if (param->bool[4] == 1)
		sort_list_time_rec(param);
}

void	 sort_list3(t_param *param)
{
	char	*tmp;

	if (param->bool[3] == 1 ?
		ft_strcmp(param->list->name, param->list->next->name) < 0 :
		ft_strcmp(param->list->name, param->list->next->name) > 0)
	{
		tmp = param->list->name;
		param->list->name = param->list->next->name;
		param->list->next->name = tmp;
		param->list = param->rec;
	}
	else
		param->list = param->list->next;
}

void	sort_swap_rec(t_param *param)
{
	char *tmp;

	tmp = param->list->name;
	param->list->name = param->list->next->name;
	param->list->next->name = tmp;
	param->list = param->rec;
}

void	 sort_list_time_rec(t_param *param)
{
	struct stat		*one;
	struct stat		*two;

	one = (struct stat*)malloc(sizeof(struct stat));
	two = (struct stat*)malloc(sizeof(struct stat));
	param->list = param->rec;
	while (param->list->next != NULL)
	{
		if (stat(param->list->name, one) == -1)
			perror("stat");
		if (stat(param->list->next->name, two) == -1)
			perror("stat");
		if (param->bool[3] == 0 ? one->st_mtime < two->st_mtime :
			one->st_mtime > two->st_mtime)
			sort_swap_rec(param);
		else if (one->st_mtime == two->st_mtime)
			sort_list3(param);
		else
			param->list = param->list->next;
	}
}
