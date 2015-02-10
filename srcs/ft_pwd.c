/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/01 18:30:27 by rbaum             #+#    #+#             */
/*   Updated: 2015/01/13 13:44:33 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_pwd(t_param *param)
{
	char	*str;

	if (param->elem != NULL)
	{
		str = ft_strdup(param->rec->name);
		str = ft_strjoin(str, "/");
		str = ft_strjoin(str, param->elem->name);
	}
	return (str);
}

char	*ft_dwp(t_param *param)
{
	char *str;

	if (param->elem->next != NULL)
	{
		str = ft_strdup(param->rec->name);
		str = ft_strjoin(str, "/");
		str = ft_strjoin(str, param->elem->next->name);
	}
	return (str);
}
