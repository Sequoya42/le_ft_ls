/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_aff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 18:56:46 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/08 13:35:59 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_pre_aff(t_param *param)
{
	unsigned int i;
	unsigned int j;

	i = ft_strlen(ft_itoa((unsigned)major(param->info.st_rdev)));
	j = ft_strlen(ft_itoa((unsigned)minor(param->info.st_rdev)));
	lstat(ft_pwd(param), &param->info);
	if ((param->group = getgrgid(param->info.st_gid)) != NULL)
	{
		if (param->tcount[0] < ft_strlen(ft_itoa(param->info.st_nlink)))
			param->tcount[0] = ft_strlen(ft_itoa(param->info.st_nlink));
	}
	if ((param->dui = getpwuid(param->info.st_uid)) != NULL)
	{
		if (param->tcount[1] < ft_strlen(param->dui->pw_name))
			param->tcount[1] = ft_strlen(param->dui->pw_name);
	}
		if (param->tcount[2] < ft_strlen(param->group->gr_name))
			param->tcount[2] = ft_strlen(param->group->gr_name);
		if (param->tcount[3] < ft_strlen(ft_itoa(param->info.st_size)))
			param->tcount[3] = ft_strlen(ft_itoa(param->info.st_size));
		if (param->tcount[4] < i)
			param->tcount[4] = i;
		if (param->tcount[5] < j)
			param->tcount[5] = j;
		param->total = param->total + param->info.st_blocks;
}

void		ft_sem_aff(t_param *param)
{
	unsigned int y;

	stat(ft_pwd(param), &param->info);
	ft_right(param);
	y = ft_strlen(ft_itoa(param->info.st_nlink));
	while (param->tcount[0] >= y++)
		ft_putchar(' ');
	ft_putnbr(param->info.st_nlink);
	y = ft_strlen(param->dui->pw_name);
	ft_putstr(" ");
		ft_putstr(param->dui->pw_name);
	while (param->tcount[1] >= y++ - 1)
		ft_putchar(' ');
	y = ft_strlen(param->group->gr_name);
	ft_putstr(param->group->gr_name);
	while (param->tcount[2] >= y++)
		ft_putchar(' ');
}

void		ft_isblk(t_param *param)
{
	unsigned int y;

	if ((S_ISBLK(param->info.st_mode)) || (S_ISCHR(param->info.st_mode)))
	{
		y = ft_strlen(ft_itoa(major(param->info.st_rdev)));
		while (param->tcount[4] >= y++)
			ft_putchar(' ');
		ft_putnbr(major(param->info.st_rdev));
		ft_putstr(",");
		y = ft_strlen(ft_itoa(minor(param->info.st_rdev)));
		while (param->tcount[5] >= y++)
			ft_putchar(' ');
		ft_putnbr(minor(param->info.st_rdev));
	}
}

void		ft_aff(t_param *param)
{
	unsigned int y;
	unsigned int i;

	i = param->tcount[4] + param->tcount[5] + 1;
	ft_sem_aff(param);
	if ((S_ISBLK(param->info.st_mode)) || (S_ISCHR(param->info.st_mode)))
		ft_isblk(param);
	else
	{
		if (i > 3)
		{
			while (i-- > 0)
				ft_putchar(' ');
		}
		y = ft_strlen(ft_itoa(param->info.st_size));
		while (param->tcount[3] >= y++)
			ft_putchar(' ');
		ft_putnbr(param->info.st_size);
	}
	ft_putchar(' ');
	ft_time(param);
	ft_putstr(param->elem->name);
}

void		print_total(t_param *param)
{
	while (param->elem)
	{
		if ((param->elem->name[0] == '.' && param->bool[2] == 1) ||
			param->elem->name[0] != '.')
		{
			ft_putstr("total ");
			ft_putnbrn(param->total);
			break ;
		}
		param->elem = param->elem->next;
	}
}
