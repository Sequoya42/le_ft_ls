/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 13:27:41 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/09 14:50:08 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <string.h>
void		sort_error(char **tmp)
{
	int		i;

	i = 0;
	while (tmp[i + 1])
	{
		if (ft_strcmp(tmp[i], tmp[i + 1]) > 0)
		{
			ft_swap(&tmp[i], &tmp[i + 1]);
			i = -1;
		}
		i++;
	}
	i = 0;
}

void		ft_error(t_param *param)
{
	struct stat		*info;
	int				i;
	int				k;
	int				l;


	k = 0;
	l = 0;
	if ((info = malloc(sizeof(struct stat))) == NULL)
		return ;
	i = ft_bool(param->av, param) + 1;
	int j = param->ac - i;
	if ((param->none = malloc(sizeof(char*) * j + 1)) == NULL)
		return;
	if ((param->reg = malloc(sizeof(char *) * j + 1)) == NULL)
		return;
	while (i < param->ac)
	{
		if (((stat(param->av[i], info)) != -1) && S_ISREG(info->st_mode))
			param->reg[k++] = param->av[i];
		else if (stat(param->av[i], info) == -1)
			 param->none[l++] = param->av[i];
		 i++;
 	} 
	opt_arg(param->reg, param);
	sort_error(param->none);
}

void	ft_aff_error(t_param *param)
{
	int i;

	i = 0;
	ft_error(param);
	while (param->none[i])
	{
		ft_putstr("ft_ls: ");
		perror(param->none[i++]);
	}
	i = 0;
	while (param->reg[i])
		ft_putendl(param->reg[i++]);
	free(param->reg);
	free(param->none);
}
