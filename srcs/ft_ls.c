/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 15:18:03 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/10 18:06:09 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_param				*param;
	struct stat			*info;
	struct s_element	*elem;
	struct s_element	*list;
	struct dirent		*dir;

	dir = (struct dirent *)malloc(sizeof(struct dirent));
	param = (t_param*)malloc(sizeof(t_param));
	info = (struct stat*)malloc(sizeof(struct stat));
	elem = (struct s_element*)malloc(sizeof(struct s_element));
	list = (struct s_element*)malloc(sizeof(struct s_element));
	param->av = av;
	param->ac = ac;
	param->dir = dir;
	param->info = *info;
	param->elem = elem;
	param->list = list;
	ft_aff_error(param);
	ft_adress(param);
	free(dir);
//	free(param);
	free(info);
	free(elem);
	free(list);
	return (0);
}

/*
Trier -R et -t en meme temps
Verifier tous les tris
Free les bons trucs pour qu'il fonctionne enfin correctmeent
*/
