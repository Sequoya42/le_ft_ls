/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 21:49:43 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/10 21:29:22 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_bool2(char **av, t_param *param, unsigned int j)
{
	int			i;

	i = 0;
	while (++i < param->ac && av[i][0] == '-' && av[i][1])
	{
		j = 1;
		while (j < ft_strlen(av[i]))
		{
			if (av[i][j] == 'l')
				param->bool[0] = 1;
			else if (av[i][j] == 'R')
				param->bool[1] = 1;
			else if (av[i][j] == 'a')
				param->bool[2] = 1;
			else if (av[i][j] == 'r')
				param->bool[3] = 1;
			else if (av[i][j] == 't')
				param->bool[4] = 1;
			else if (av[i][j] == '-')
				return (param->count_opt = i);
			else if (av[i][j] != '1')
				ft_bool_error(av, i, j);
			j++;
		}
	}
	return (param->count_opt = i - 1);
}

int			ft_bool(char **av, t_param *param)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 1;
	while (param->bool[i])
		param->bool[i++] = 0;
	k = ft_bool2(av, param, j);
	k = k;
	return (param->count_opt);
}

int			ft_bool_error(char **av, int i, int j)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(av[i][j]);
	ft_putchar('\n');
	ft_putendl("usage: ft_ls [Ralrt] [file ...]");
	exit(0);
}

int			ft_hide(t_param *param)
{
	int size;
	int i;

	i = 0;
	size = ft_strlen(param->rec->name) - 1;
	while (size != 0 && param->rec->name[size] != '/')
	{
		if (param->rec->name[size] == '.' && param->rec->name[size - 1] != '.'
			&& param->bool[2] == 0)
			i = 1;
		size--;
	}
	return (i);
}
