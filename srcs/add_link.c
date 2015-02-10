/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 12:04:50 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/10 17:56:31 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		add_link(t_param *param)
{
	t_element	*new;
	t_element	*begin;

	if ((new = (t_element *)malloc(sizeof(t_element))) == NULL)
		return ;
	new->name = ft_strdup(param->dir->d_name);
	new->next = NULL;
	if (param->elem == NULL)
		param->elem = new;
	else
	{
		begin = param->elem;
		while (begin->next &&
			   (param->bool[3] == 0 ? ft_strcmp(begin->next->name, new->name) < 0 : 
				ft_strcmp(begin->next->name, new->name) > 0))
			begin = begin->next;
			new->next = begin->next;
			begin->next = new;
	}
}

void		add_list(t_param *param)
{
	t_element	*new;
	t_element	*begin;

	if ((new = (t_element *)malloc(sizeof(t_element))) == NULL)
		return ;
	new->name = ft_strdup(param->rec->name);
	new->name = ft_strjoin(new->name, "/");
	new->name = ft_strjoin(new->name, param->dir->d_name);
	new->next = NULL;
	if (param->listime == NULL)
		param->listime = new;
	else
	{
		begin = param->listime;
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = new;
	}
}

void		add_rec_link(t_param *param)
{
	t_element	*new;
	t_element	*begin;

	if ((new = (t_element *)malloc(sizeof(t_element))) == NULL)
		return ;
	new->name = ft_strdup(param->rec->name);
	new->name = ft_strjoin(new->name, "/");
	new->name = ft_strjoin(new->name, param->dir->d_name);
	new->next = NULL;
	if (param->rec == NULL)
		param->rec = new;
	else
	{
		begin = param->rec;
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = new;
	}
}

void		add_av(t_param *param)
{
	t_element	*new;
	t_element	*begin;

	if ((new = (t_element *)malloc(sizeof(t_element))) == NULL)
		return ;
	new->name = ft_strdup(param->av[param->i]);
	new->next = NULL;
	if (param->rec == NULL)
		param->rec = new;
	else
	{
		begin = param->rec;
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = new;
	}
}

void		add_if_none(t_param *param)
{
	t_element	*new;

	if ((new = (t_element *)malloc(sizeof(t_element))) == NULL)
		return ;
	param->j += 1;
	new->name = ft_strdup(".");
	new->next = NULL;
	param->rec = new;
}
