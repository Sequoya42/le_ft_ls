/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adress.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 16:58:36 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/09 21:33:19 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_printer(t_param *param)
{
	while (param->elem != NULL)
	{
		if ((param->elem->name[0] == '.' && param->bool[2] == 1) ||
			param->elem->name[0] != '.')
			ft_putendl(param->elem->name);
		param->elem = param->elem->next;
	}
	free(param->elem);
	param->elem = NULL;
}

void	ft_option(t_param *param)
{
	sort_list(param);
	if (param->bool[4] == 1)
	{
		sort_equ(param);
		sort_list_time(param);
	}
	if (param->bool[0] == 1 && ft_hide(param) == 0)
		ft_ls_l(param);
}

void	ft_print(t_param *param)
{
	param->elem = NULL;
	param->list = NULL;
	while ((param->dir = readdir(param->dirp)) != NULL)
	{
		add_link(param);
		add_list(param);
		if (param->dir->d_type == DT_DIR && (param->bool[1] == 1)
			&& (ft_strcmp(param->dir->d_name, ".") != 0)
			&& (ft_strcmp(param->dir->d_name, "..") != 0))
			add_rec_link(param);
	}
	ft_option(param);
	if (ft_hide(param) == 0)
		ft_printer(param);
}

void	ft_multad(t_param *param)
{
	if (param->rec)
		ft_option_rec(param);
	if ((param->dirp = opendir(param->rec->name)) == NULL)
		return ;
	else
	{
		if (param->j >= 2 && ft_hide(param) == 0)
		{
			ft_putstr(param->rec->name);
			ft_putendl(":");
		}
		ft_print(param);
		closedir(param->dirp);
		if (param->rec->next && ft_hide(param) == 0)
		ft_putchar('\n');
	}
	free(param->rec);
}

void	ft_adress(t_param *param)
{
	param->i = ft_bool(param->av, param);
	param->j = ((param->ac - param->i) - 1);
	param->i++;
	opt_arg(param->av, param);
	if (param->av[param->i])
	{
		add_av(param);
		param->i++;
	}
	if (param->j == 0)
		add_if_none(param);
	while (param->rec)
	{
		ft_multad(param);
		param->rec = param->rec->next;
		param->j++;
		ft_add_av(param);
	}
	free(param->rec);
	free(param);
}
