/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 15:25:00 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/09 15:04:30 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	opt_arg(char **tmp, t_param *param)
{
	sort_arg(tmp, param);
	if (param->bool[4] == 1)
		sort_arg_time(tmp, param);
}

void	ft_swap(char **a, char **b)
{

	char *tmp;
	if (*a && *b)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

void	sort_arg(char **tmp, t_param *param)
{
	int i;

	i = param->i;
	while (tmp[i + 1])
	{
		if (param->bool[3] == 1 ? 
			(ft_strcmp(tmp[i], tmp[i + 1]) < 0) :
			(ft_strcmp(tmp[i], tmp[i + 1]) > 0))
		{
			ft_swap(&tmp[i], &tmp[i + 1]);
			i = param->i;
			if (i == 0)
				i--;
		}
		i++;
	}
}

void	sort_arg_time(char **tmp, t_param *param)
{
	int				i;
	struct stat		*one;
	struct stat		*two;

	i = param->i;
	one = (struct stat*)malloc(sizeof(struct stat));
	two = (struct stat*)malloc(sizeof(struct stat));
	if (tmp[i])
	{
		while (tmp[i + 1])
		{
			if (stat(tmp[i], one) == -1)
				perror("stat");
			if (stat(tmp[i + 1], two) == -1)
				perror("stat");
			if (param->bool[3] == 0 ? one->st_mtime < two->st_mtime : 
				one->st_mtime > two->st_mtime)
			{
				ft_swap(&tmp[i], &tmp[i + 1]);
				i = param->i - 1;
			}
			i++;
		}
	}
}

void	ft_add_av(t_param *param)
{
	struct stat		*info;
	if ((info = malloc(sizeof(struct stat))) == NULL)
		return;
	if (!param->rec && param->av[param->i])
	{
		if ((stat(param->av[param->i], info)) != -1 && S_ISDIR(info->st_mode))
			ft_putchar('\n');
		add_av(param);
		param->i++;
	}
}
